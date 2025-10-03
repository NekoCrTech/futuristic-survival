// developed by Neko

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
	FText GetInteractionText_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(class ASurvCharacter* Caller);
	void Interact_Implementation(class ASurvCharacter* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool IsInteractable() const;
	bool IsInteractable_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SetInteractionWidgetIsEnabled(bool bIsEnabled);
	
};
