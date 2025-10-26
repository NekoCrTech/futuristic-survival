// developed by Neko


#include "Character/SurvEnemyCharacter.h"

#include "AbilitySystem/SurvAbilitySystemComponent.h"
#include "AbilitySystem/SurvAttributeSet.h"


ASurvEnemyCharacter::ASurvEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<USurvAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USurvAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASurvEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASurvEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ASurvEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent()))return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	if (HasAuthority())
	{
		GiveStartupAbilities();
		InitializeAttributes();
	}
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
}

