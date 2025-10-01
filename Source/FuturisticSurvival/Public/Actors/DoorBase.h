// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "DoorBase.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API ADoorBase : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, meta = (AllowPrivateAccess = "true"))
	bool bIsOpen = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, meta = (AllowPrivateAccess = "true"))
	bool bIsOpening = false;
	
protected:
	
public:

	ADoorBase();

	FText GetInteractionText_Implementation();
	void Interact_Implementation(class ASurvCharacter* Caller);
	bool IsInteractable_Implementation() const;
	
};
