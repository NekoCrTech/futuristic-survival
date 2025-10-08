// developed by Neko
//TODO: Rework implementation functions where needed

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};


class FUTURISTICSURVIVAL_API IInteractionInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionText();
	virtual FText GetInteractionText_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(class ASurvCharacter* Caller);
	virtual void Interact_Implementation(class ASurvCharacter* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool IsInteractable() const;
	virtual bool IsInteractable_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SetInteractionWidgetIsEnabled(bool bIsEnabled);
	virtual void SetInteractionWidgetIsEnabled_Implementation(bool bIsEnabled);
	
};
