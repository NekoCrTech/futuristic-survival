// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "SurvContainer.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ASurvContainer : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	
	ASurvContainer();

	virtual FText GetInteractionText_Implementation() override;
	virtual void Interact_Implementation(class ASurvCharacter* Caller) override;
	virtual bool IsInteractable_Implementation() const override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Survival|Components", Meta=(AllowPrivateAccess="true"))
	class UInventoryComponent* InventoryComponent;
};
