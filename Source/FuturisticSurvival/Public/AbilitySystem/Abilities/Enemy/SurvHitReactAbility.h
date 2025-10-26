// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Abilitysystem/Abilities/SurvGameplayAbility.h"
#include "SurvHitReactAbility.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvHitReactAbility : public USurvGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Survival|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);

	UPROPERTY(BlueprintReadOnly, Category = "Survival|Abilities")
	FVector AvatarForward;
	UPROPERTY(BlueprintReadOnly, Category = "Survival|Abilities")
	FVector ToInstigator;
};
