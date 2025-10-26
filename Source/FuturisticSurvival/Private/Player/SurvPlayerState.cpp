// developed by Neko


#include "Player/SurvPlayerState.h"
#include "AbilitySystem/SurvAbilitySystemComponent.h"


ASurvPlayerState::ASurvPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<USurvAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsNetStartupComponent(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASurvPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
