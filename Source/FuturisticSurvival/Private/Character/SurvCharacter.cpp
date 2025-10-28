// Developed by Neko


#include "Public/Character/SurvCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Structs/SaveActorData.h"
#include "Components/StatlineComponent.h"
#include "InventorySystem/InventoryComponent.h"
#include "Net/UnrealNetwork.h"


ASurvCharacter::ASurvCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
	Statline->SetMovementCompReference(GetCharacterMovement());

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	SaveActorID = FGuid::NewGuid();
}

void ASurvCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!SaveActorID.IsValid())
	{
		SaveActorID = FGuid::NewGuid();
	}
}

void ASurvCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
}

bool ASurvCharacter::CanCharJump() const
{
	return Statline->CanJump();
}

void ASurvCharacter::HasJumped()
{
	Statline->HasJumped();
	ACharacter::Jump();
}

bool ASurvCharacter::CanSprint() const
{
	return Statline->CanSprint();
}

void ASurvCharacter::SetSprinting(const bool& IsSprinting)
{
	Statline->SetSprinting(IsSprinting);
}

void ASurvCharacter::SetSneaking(const bool& IsSneaking)
{
	Statline->SetSneaking(IsSneaking);
}

void ASurvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* ASurvCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

FGuid ASurvCharacter::GetActorSaveID_Implementation()
{
	
	return SaveActorID;
}

FSaveActorData ASurvCharacter::GetSaveData_Implementation()
{
	return FSaveActorData(this->GetTransform(), this->bWasSpawned, this->GetClass());
}

void ASurvCharacter::SetActorGUID_Implementation(const FGuid& NewGiud)
{
	if (SaveActorID.IsValid())
	{
		SaveActorID.Invalidate();
	}

	SaveActorID = NewGiud;
}

void ASurvCharacter::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}

// ABILITY SYSTEM

void ASurvCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ASurvCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set."))

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ASurvCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
}

void ASurvCharacter::HandleDeath()
{
	bAlive = false;

	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red, FString::Printf(TEXT("SurvCharacter::HandleDeath() - %s is dead"), *GetName()));
	}
}

void ASurvCharacter::HandleRespawn()
{
	bAlive = true;
}



