// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "SurvPlayerState.generated.h"

class USurvAttributeSet;
class USurvAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API ASurvPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASurvPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Survival|Abilities")
	TObjectPtr<USurvAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USurvAttributeSet> AttributeSet;
};
