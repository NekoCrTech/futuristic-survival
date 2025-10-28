// developed by Neko


#include "Character/SurvEnemyCharacter.h"

#include "AIController.h"
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

void ASurvEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent()))return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	InitializeAttributes();

	USurvAttributeSet* SurvAttributeSet = Cast<USurvAttributeSet>(GetAttributeSet());
	if (!IsValid(SurvAttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(SurvAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	
}

void ASurvEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();

	AAIController* AIController = GetController<AAIController>();
	if (!IsValid(AIController)) return;
	AIController->StopMovement();
}

UAbilitySystemComponent* ASurvEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASurvEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}



