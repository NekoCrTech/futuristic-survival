// Developed by Neko


#include "Components/StatlineComponent.h"

#include "SurvUtils.h"
#include "Logger.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void UStatlineComponent::SetMovementCompReference(UCharacterMovementComponent* Comp)
{
	OwningCharMovementComponent = Comp;
}

void UStatlineComponent::TickStats(const float& DeltaTime)
{
	TickStamina(DeltaTime);
	Energy.TickStat(DeltaTime);
	TickThirst(DeltaTime);
	TickHunger(DeltaTime);
	if (Hunger.HasEnough() && Thirst.HasEnough())
	{
		Health.TickStat(DeltaTime);
	}
}

void UStatlineComponent::TickStamina(const float& DeltaTime)
{
	if (CurrentStaminaExhaustion > 0.f)
	{
		CurrentStaminaExhaustion -= DeltaTime;
		return;
	}
	if (bIsSprinting && IsValidSprinting())
	{
		Stamina.TickStat(0 - abs(DeltaTime * SprintCostMultiplier));
		if (Stamina.GetCurrent()<=0.f)
		{
			SetSprinting(false);
			CurrentStaminaExhaustion = StaminaExhaustionDuration;
		}
		return;
	}
	Stamina.TickStat(DeltaTime);
}

void UStatlineComponent::TickHunger(const float& DeltaTime)
{
	if (Hunger.GetCurrent() <= 0.f)
	{
		Health.Adjust(0 - abs(HungerDps * DeltaTime));
		return;
	}
	Hunger.TickStat(DeltaTime);
}

void UStatlineComponent::TickThirst(const float& DeltaTime)
{
	if (Thirst.GetCurrent() <= 0.f)
	{
		Health.Adjust(0 - abs(ThirstDps * DeltaTime));
		return;
	}
	Thirst.TickStat(DeltaTime);
}

bool UStatlineComponent::IsValidSprinting()
{
	return OwningCharMovementComponent->Velocity.Length() > WalkSpeed && !OwningCharMovementComponent->IsFalling();
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
		Logger::GetInstance()->AddMessage("UStatlineComponent::GetStatPercentile called with invalid stat type", ERRORLEVEL::EL_WARNING);
		break;
	}
	return -1.f;
}

void UStatlineComponent::AdjustStat(const EStat& Stat, const float& Amount)
{
	switch (Stat)
	{
	case EStat::Health:
		Health.Adjust(Amount);
	case EStat::Stamina:
		Stamina.Adjust(Amount);
	case EStat::Energy:
		Energy.Adjust(Amount);
	case EStat::Thirst:
		Thirst.Adjust(Amount);
	case EStat::Hunger:
		Hunger.Adjust(Amount);
	default:
		Logger::GetInstance()->AddMessage("UStatlineComponent::AdjustStat called with invalid stat type", ERRORLEVEL::EL_WARNING);
		break;
	}
	
}

bool UStatlineComponent::CanSprint() const
{
	return Stamina.HasEnough();
}

void UStatlineComponent::SetSprinting(const bool IsSprinting)
{
	bIsSprinting = IsSprinting;
	if (bIsSneaking && !bIsSprinting)
	{
		return;
	}
	bIsSneaking = false;
	OwningCharMovementComponent->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

void UStatlineComponent::SetSneaking(const bool IsSneaking)
{
	bIsSneaking = IsSneaking;
	if (bIsSprinting && !bIsSneaking)
	{
		return;
	}
	bIsSprinting = false;
	OwningCharMovementComponent->MaxWalkSpeed = bIsSneaking ? SneakSpeed : WalkSpeed;
}

bool UStatlineComponent::CanJump()
{
	return Stamina.HasEnough(JumpCost);
}

void UStatlineComponent::HasJumped()
{
	Stamina.Adjust(0-JumpCost);
}

FSaveComponentData UStatlineComponent::GetSaveComponentData_Implementation()
{
	FSaveComponentData Ret;

	Ret.ComponentClass = this->GetClass();
	Ret.RawData.Add(Health.GetSaveString()); // index: 0
	Ret.RawData.Add(Stamina.GetSaveString()); // index: 1
	Ret.RawData.Add(Energy.GetSaveString()); // index: 2
	Ret.RawData.Add(Thirst.GetSaveString()); // index: 3
	Ret.RawData.Add(Hunger.GetSaveString()); // index: 4
	// Any addition raw data adds here, need to be included in SetSaveComponentData_Implementation function
	
	return Ret;
}

void UStatlineComponent::SetSaveComponentData_Implementation(FSaveComponentData Data)
{
	TArray<FString> Parts;
	for (int i = 0; i < Data.RawData.Num(); i++)
	{
		Parts.Empty();
		Parts = ChopString(Data.RawData[i], '|');
		switch (i)
		{
			case 0:
				Health.UpdateFromSaveString(Parts);
				break;
			case 1:
				Stamina.UpdateFromSaveString(Parts);
				break;
			case 2:
				Energy.UpdateFromSaveString(Parts);
				break;
			case 3:
				Thirst.UpdateFromSaveString(Parts);
				break;
			case 4:
				Hunger.UpdateFromSaveString(Parts);
				break;
		default:
				// TODO:Log Error
				break;
			
		}
	}
}

