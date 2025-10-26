// developed by Neko


#include "Abilitysystem/Abilities/SurvGameplayAbility.h"

void USurvGameplayAbility::DrawDebugActivationMessage()
{
	if (bDrawDebug == true)
	{
		const FString ActorName = GetAvatarActorFromActorInfo()->GetName();
		const FString AbilityName = GetName();
		const FString DebugMessage = FString::Printf(TEXT("The %s activated %s"), *ActorName, *AbilityName);

		GEngine->AddOnScreenDebugMessage(
			-1,               // key (-1 means create new message)
			3.f,              // display time
			FColor::Yellow,   // color
			DebugMessage      // message
		);
	}
}
