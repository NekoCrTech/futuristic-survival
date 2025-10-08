// developed by Neko


#include "Actors/Chronomanager.h"

#include "Logger.h"
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

void AChronomanager::UpdateFromSave_Implementation()
{
	CalculateDayLength();
	UpdateTimeOfDay();
	UpdateLightRotation();
	UpdateLighting();
	SunLight->GetLightComponent()->UpdateColorAndBrightness();
}

void AChronomanager::CalculateDayLength()
{
	MinuteLength = (DayLengthInMinutes*60.f) / 1440.f;
	TimeDecay = MinuteLength;
}

void AChronomanager::UpdateTimeOfDay()
{
	CurrentTimeOfDay = (CurrentTime.Hour * 60) + CurrentTime.Minute;
}

//---------------
// Advance Time
//---------------

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
	if (!IsValid(SunLight) || !IsValid(DailySunlightIntensity))
	{
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLighting - Directional light or Daily Sun Intensity is invalid", EL_ERROR);
		return;
	}
	
	float NewLightIntensity = DailySunlightIntensity->GetFloatValue(CurrentTimeOfDay);
	if(IsValid(AnnualSunlightIntensity))
	{
		NewLightIntensity += AnnualSunlightIntensity->GetFloatValue(CurrentTime.DayOfYear);
	}
	NewLightIntensity = FMath::Clamp(NewLightIntensity, 0.0f, MaxSunlightIntensity);

	SunLight->GetLightComponent()->Intensity = NewLightIntensity;
	
	if (!IsValid(SkyLight) || !IsValid(SkylightIntensity))
	{
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLighting - Skylight or Skylight Intensity is invalid", EL_ERROR);
		return;
	}

	float NewSkylightIntensity = SkylightIntensity->GetFloatValue(CurrentTimeOfDay);
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
		Logger::GetInstance()->AddMessage("AChronomanager::UpdateLightRotation - Directional light or Daily Sun Rotation is invalid", EL_ERROR);
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





