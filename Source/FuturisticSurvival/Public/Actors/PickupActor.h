// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "PickupActor.generated.h"


UCLASS()
class FUTURISTICSURVIVAL_API APickupActor : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	APickupActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");
	

protected:

public:

	FText GetInteractionText_Implementation();
	void Interact_Implementation(class ASurvCharacter* Caller);
	bool IsInteractable_Implementation();
	
	
};
