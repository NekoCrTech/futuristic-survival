// developed by Neko


#include "Abilitysystem/Abilities/SurvGameplayAbility.h"

void USurvGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	DrawDebugMessage("Activated");
}

void USurvGameplayAbility::DrawDebugMessage(const FString& Message)
{
	if (bDrawDebug == true)
	{
		const FString ActorName = GetAvatarActorFromActorInfo()->GetName();
		const FString AbilityName = GetName();
		const FString DebugMessage = FString::Printf(TEXT("%s - %s: %s"), *ActorName, *AbilityName, *Message);

		GEngine->AddOnScreenDebugMessage(
			-1,               // key (-1 means create new message)
			5.f,              // display time
			FColor::Yellow,   // color
			DebugMessage      // message
		);
	}
}
