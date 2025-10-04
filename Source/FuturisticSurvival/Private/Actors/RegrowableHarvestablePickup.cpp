// developed by Neko


#include "Actors/RegrowableHarvestablePickup.h"

void ARegrowableHarvestablePickup::ResetHarvest()
{
	bIsHarvested = false;
	ItemCount=ItemRegrowthAmount;
	ChangeMeshCompVisibility(HarvestMesh, true, ECollisionEnabled::QueryOnly);
	MarkComponentsRenderStateDirty();
}

void ARegrowableHarvestablePickup::BeginPlay()
{
	Super::BeginPlay();
	//TODO: Subscribe to DayChange Delegate
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
