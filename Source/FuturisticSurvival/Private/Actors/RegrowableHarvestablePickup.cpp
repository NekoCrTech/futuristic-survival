// developed by Neko


#include "Actors/RegrowableHarvestablePickup.h"
#include "Logger.h"
#include "SurvUtils.h"
#include "Actors/Chronomanager.h"
#include "Kismet/GameplayStatics.h"

void ARegrowableHarvestablePickup::BeginPlay()
{
	Super::BeginPlay();
	TimeManager = Cast<AChronomanager>(UGameplayStatics::GetActorOfClass(GetWorld(),AChronomanager::StaticClass()));
	if (!IsValid(TimeManager))
	{
		Logger::GetInstance()->AddMessage("ARegrowableHarvestablePickup - Chronomanager is invalid", EL_ERROR);
		return;
	}
	TimeManager->OnTimeChange.AddUniqueDynamic(this, &ARegrowableHarvestablePickup::OnTimeChanged);
}

void ARegrowableHarvestablePickup::ResetHarvest()
{
	bIsHarvested = false;
	ItemCount=ItemRegrowthAmount;
	ChangeMeshCompVisibility(HarvestMesh, true, ECollisionEnabled::QueryOnly);
	MarkComponentsRenderStateDirty();
}

void ARegrowableHarvestablePickup::OnDayChanged()
{
	DaysSinceLastHarvest++;
	if(DaysSinceLastHarvest < NO_DaysToRegrow)
	{
		return;
	}
	ResetHarvest();	
}

void ARegrowableHarvestablePickup::OnTimeChanged(FTimeData TimeData)
{
	if(!bIsHarvested)
	{
		return;
	}
	if(TimeData.Day == HarvestTracking.Day)
	{
		return;
	}
	OnDayChanged();
	HarvestTracking = TimeData;
}

void ARegrowableHarvestablePickup::Interact_Implementation(class ASurvCharacter* Caller)
{
	Super::Interact_Implementation(Caller);
	if (!IsValid(TimeManager))
	{
		Logger::GetInstance()->AddMessage("ARegrowableHarvestablePickup - Chronomanager is invalid", EL_ERROR);
		return;
	}
	if (!bIsHarvested)
	{
		return;
	}
	HarvestTracking = TimeManager->GetCurrentGameTime();
	DaysSinceLastHarvest = 0;
}

FSaveActorData ARegrowableHarvestablePickup::GetSaveData_Implementation()
{
	TArray<FString> RawData;
	RawData.Add(HarvestTracking.GetSaveString());
	return FSaveActorData(GetActorTransform(),bWasSpawned,GetClass()->StaticClass(),RawData);
}

void ARegrowableHarvestablePickup::UpdateFromSave_Implementation()
{
	Super::UpdateFromSave_Implementation();
}

void ARegrowableHarvestablePickup::SetActorRawSaveData_Implementation(const TArray<FString>& RawData)
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
			HarvestTracking.UpdateFromSaveString(chunks);
			break;
		default:
			Logger::GetInstance()->AddMessage("ARegrowableHarvestablePickup::SetActorRawSaveData_Implementation - Out of expected index", EL_ERROR);
			break;
		}
	}
}
