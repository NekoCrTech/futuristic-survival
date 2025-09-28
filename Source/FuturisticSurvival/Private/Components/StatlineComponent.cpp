// Developed by Neko


#include "Components/StatlineComponent.h"

// Sets default values for this component's properties
UStatlineComponent::UStatlineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UStatlineComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UStatlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickType != LEVELTICK_PauseTick)
	{
		TickStats(DeltaTime);
	}
}

void UStatlineComponent::TickStats(const float& DeltaTime)
{
	Health.TickStat(DeltaTime);
	Stamina.TickStat(DeltaTime);
	Energy.TickStat(DeltaTime);
	Thirst.TickStat(DeltaTime);
	Hunger.TickStat(DeltaTime);
}

float UStatlineComponent::GetStatPercentile(const EStat Stat) const
{
	switch (Stat)
	{
	case EStat::Health:
		return Health.Percentile();
	case EStat::Stamina:
		return Stamina.Percentile();
	case EStat::Energy:
		return Energy.Percentile();
	case EStat::Thirst:
		return Thirst.Percentile();
	case EStat::Hunger:
		return Hunger.Percentile();
	default:
		//TODO: Log invalid stat;
		break;
	}
	return -1.f;
}

