// developed by Neko


#include "Player/SurvPlayerState.h"
#include "AbilitySystemComponent.h"

ASurvPlayerState::ASurvPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsNetStartupComponent(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASurvPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
