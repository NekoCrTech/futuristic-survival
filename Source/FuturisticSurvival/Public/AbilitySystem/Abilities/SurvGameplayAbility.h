// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SurvGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Survival|Debug")
	bool bDrawDebug = false;

	UFUNCTION(BlueprintCallable, Category = "Survival|Debug")
	void DrawDebugMessage(const FString& Message);

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
