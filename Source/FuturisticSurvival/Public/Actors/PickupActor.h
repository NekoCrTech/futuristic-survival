// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "PickupActor.generated.h"


class UItemBase;

UCLASS()
class FUTURISTICSURVIVAL_API APickupActor : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	APickupActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemBase> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");
	

protected:

public:

	UFUNCTION(BlueprintCallable)
	FText GetInteractionText_Implementation() override;
	void Interact_Implementation(class ASurvCharacter* Caller)override;
	bool IsInteractable_Implementation() const override;
	
	
};
