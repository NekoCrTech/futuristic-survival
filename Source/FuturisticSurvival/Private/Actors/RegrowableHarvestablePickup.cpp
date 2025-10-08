// developed by Neko


#include "Actors/RegrowableHarvestablePickup.h"
#include "Logger.h"
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
