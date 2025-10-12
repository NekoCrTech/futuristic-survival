// developed by Neko


#include "Actors/Chronomanager.h"

#include "Logger.h"
#include "SurvUtils.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"




void AChronomanager::BeginPlay()
{
	
	Super::BeginPlay();
	CalculateDayLength();
	SetStartDate();
	SetDayOfYear();
	GetWorld()->GetTimerManager().SetTimer(WorldTemperatureHandle, this, &AChronomanager::UpdateTemperature, WorldTempTickRate, true,0);
}

void AChronomanager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(WorldTemperatureHandle);
	Super::EndPlay(EndPlayReason);
}

void AChronomanager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bUseDayNightCycle)
	{
		return;
	}
	UpdateTime(DeltaTime);
	UpdateTimeOfDay();
	UpdateLightRotation();
	UpdateLighting();
	SunLight->GetLightComponent()->UpdateColorAndBrightness();
	if(bTimeWasUpdated)
	{
		OnTimeChange.Broadcast(CurrentTime);
	}
	
}

//---------------
// Time
//---------------

void AChronomanager::CalculateDayLength()
{
	MinuteLength = (DayLengthInMinutes*60.f) / 1440.f;
	TimeDecay = MinuteLength;
	WorldTempTickRate = MinuteLength * 15.f;
}

void AChronomanager::UpdateTimeOfDay()
{
	CurrentTimeOfDay = (CurrentTime.Hour * 60) + CurrentTime.Minute;
}

void AChronomanager::SetStartDate()
{
	if (!bUseStartDate)
	{
		return;
	}
	CurrentTime.Day = StartDay;
	CurrentTime.Month = StartMonth;
	CurrentTime.Year = StartYear;
}

void AChronomanager::UpdateTime(const float& DeltaTime)
{
	TimeDecay -= DeltaTime;
	if (TimeDecay <= 0.0f)
	{
		TimeDecay += MinuteLength;
		AdvanceMinute();
	}
}

void AChronomanager::AdvanceMinute()
{
	bTimeWasUpdated = true;
	CurrentTime.Minute++;
	if (CurrentTime.Minute >= 60)
	{
		CurrentTime.Minute = 0;
		AdvanceHour();
	}
}

void AChronomanager::AdvanceHour()
{
	bTimeWasUpdated = true;
	CurrentTime.Hour++;
	if (CurrentTime.Hour >= 24)
	{
		CurrentTime.Hour = 0;
		AdvanceDay();
	}
}

void AChronomanager::AdvanceDay()
{
	bTimeWasUpdated = true;
	SetDayOfYear();
	CurrentTime.Day++;
	if (CurrentTime.Day >= FDateTime::DaysInMonth(CurrentTime.Year, CurrentTime.Month))
	{
		CurrentTime.Day = 1;
		AdvanceMonth();
	}
}

void AChronomanager::AdvanceMonth()
{
	bTimeWasUpdated = true;
	CurrentTime.Month++;
	if (CurrentTime.Month >= 12)
	{
		CurrentTime.Month = 1;
		AdvanceYear();
	}
}

void AChronomanager::AdvanceYear()
{
	bTimeWasUpdated = true;
	CurrentTime.Year++;
}

void AChronomanager::SetDayOfYear()
{
	CurrentTime.DayOfYear = FDateTime(CurrentTime.Year, CurrentTime.Month, CurrentTime.Day).GetDayOfYear() + 1;
}

//-----------
// Lighting
//-----------

void AChronomanager::UpdateLighting()
{
	if (!IsValid(SunLight) || !IsValid(DailySunlightRotation))
	{
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLighting - Directional light or Daily Sun Intensity is invalid", EErrorLevel::EL_ERROR);
		return;
	}
	float NewLightIntensity = DailySunlightRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	if(IsValid(AnnualSunlightRotation))
	{
		NewLightIntensity += AnnualSunlightRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	}
	NewLightIntensity = FMath::Clamp(NewLightIntensity, 0.0f, MaxSunlightIntensity);

	SunLight->GetLightComponent()->Intensity = NewLightIntensity;
	
	if (!IsValid(SkyLight) || !IsValid(SkylightHourlyColor))
	{
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLighting - Skylight or Skylight Intensity is invalid", EErrorLevel::EL_ERROR);
		return;
	}

	float NewSkylightIntensity = SkylightHourlyColor->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	SkyLight->GetLightComponent()->SetIntensity(NewSkylightIntensity);
	if (IsValid(SkylightHourlyColor))
	{
		FLinearColor NewSkylightColor = SkylightHourlyColor->GetLinearColorValue(CurrentTimeOfDay);
		SkyLight->GetLightComponent()->SetLightColor(NewSkylightColor);
	}
}

void AChronomanager::UpdateLightRotation()
{
	if (!IsValid(SunLight) || !IsValid(DailySunlightRotation))
	{
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLightRotation - Directional light or Daily Sun Rotation is invalid", EErrorLevel::EL_ERROR);
		return;
	}
	
	FLinearColor ColorAsRotation = DailySunlightRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
	if (IsValid(AnnualSunlightRotation))
	{
		ColorAsRotation += AnnualSunlightRotation->GetUnadjustedLinearColorValue(CurrentTime.DayOfYear);
	}
	FRotator NewRot(ColorAsRotation.G, ColorAsRotation.B, ColorAsRotation.R);

	SunLight->SetActorRotation(NewRot);
}

//---------------
// Temperature
//---------------

void AChronomanager::UpdateTemperature()
{
	if(!IsValid(DailyTemperatureRange) || !IsValid(AnnualTemperatureRange))
	{
		GetWorld()->GetTimerManager().ClearTimer(WorldTemperatureHandle);
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateTemperature - Daily or Annual temperature range is invalid", EErrorLevel::EL_WARNING);
		return;
	}

	float CurrentDaily = DailyTemperatureRange->GetFloatValue(CurrentTimeOfDay);
	float CurrentAnnual = AnnualTemperatureRange->GetFloatValue(CurrentTime.DayOfYear);

	// Random range 5°C (-2.5 , 2.5)
	CurrentWorldTemp = CurrentDaily + CurrentAnnual + FMath::FRandRange(-5.f, 5.f);
	OnTemperatureChange.Broadcast(CurrentWorldTemp);
}


// Save & Load

void AChronomanager::UpdateFromSave_Implementation()
{
	CalculateDayLength();
	UpdateTimeOfDay();
	UpdateLightRotation();
	UpdateLighting();
	SunLight->GetLightComponent()->UpdateColorAndBrightness();
}

FSaveActorData AChronomanager::GetSaveData_Implementation()
{
	TArray<FString> RawData;
	RawData.Add(CurrentTime.GetSaveString());
	return FSaveActorData(GetActorTransform(),bWasSpawned,GetClass()->StaticClass(),RawData);
}

void AChronomanager::SetActorRawSaveData_Implementation(const TArray<FString>& RawData)
{
	int i=0;
	TArray<FString> chunks;
	for (auto d : RawData)
	{
		chunks.Empty();
		switch(i)
		{
		case 0:
			chunks = ChopString(d,'|');
			CurrentTime.UpdateFromSaveString(chunks);
			break;
		default:
			Logger::GetInstance()->AddMessage("AChronomanager::SetActorRawSaveData_Implementation - Out of expected index", EErrorLevel::EL_ERROR);
			break;
		}
	}
}





