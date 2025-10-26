// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SurvGasWidgetComponent.generated.h"

class USurvAttributeSet;
class ASurvCharacter;
class USurvAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvGasWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	

protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<ASurvCharacter> SurvCharacter;
	TWeakObjectPtr<USurvAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<USurvAttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAtributeDelegate();

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
	
	
};
