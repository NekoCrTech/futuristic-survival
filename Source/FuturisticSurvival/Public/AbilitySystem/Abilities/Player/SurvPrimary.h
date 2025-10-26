// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Abilitysystem/Abilities/SurvGameplayAbility.h"
#include "SurvPrimary.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvPrimary : public USurvGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Survival|Ability")
	void HitBoxOverlapTest();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Survival|Ability")
	float HitBoxRadius = 80.f;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Ability")
	float HitBoxForwardOffset = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Ability")
	float HitBoxElevationOffset = 20.f;
};
