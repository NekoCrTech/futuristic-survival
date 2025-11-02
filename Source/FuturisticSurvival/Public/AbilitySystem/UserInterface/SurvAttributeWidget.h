// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "AbilitySystem/SurvAttributeSet.h"
#include "SurvAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvAttributeWidget : public USurvUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Attributes")
	FGameplayAttribute Attribute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Attributes")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, USurvAttributeSet* AttributeSet);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue);
	
	
};
