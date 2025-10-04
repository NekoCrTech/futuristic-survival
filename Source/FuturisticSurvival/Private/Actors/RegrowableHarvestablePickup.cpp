// developed by Neko


#include "Actors/RegrowableHarvestablePickup.h"

ARegrowableHarvestablePickup::ARegrowableHarvestablePickup() : AHarvestablePickup()
{

}

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

void ARegrowableHarvestablePickup::OnDaychanged()
{
	DaysSinceLastHarvest++;
	if(DaysSinceLastHarvest < NO_DaysToRegrow)
	{
		return;
	}
	ResetHarvest();	
}
