// developed by Neko


#include "Character/SurvEnemyCharacter.h"

#include "AbilitySystemComponent.h"


ASurvEnemyCharacter::ASurvEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ASurvEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASurvEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(AbilitySystemComponent))return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);

	if (!HasAuthority())return;
	GiveStartupAbilities();
}

