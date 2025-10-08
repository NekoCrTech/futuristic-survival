// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "HarvestablePickup.generated.h"

/**
 * HarvestablePickup actor is for resources than can be harvested with hands and will not regrow like a Mercer Sphere
 */

class UItemBase;

UCLASS()
class FUTURISTICSURVIVAL_API AHarvestablePickup : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemBase> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");

protected:

	// Permanent Mesh should be empty for one time harvestables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PermanentMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HarvestMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bIsHarvested = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;
	
	
	AHarvestablePickup();

	void UpdateHarvestState();

public:
	
	UFUNCTION(BlueprintCallable)
	virtual FText GetInteractionText_Implementation() override;
	virtual void Interact_Implementation(class ASurvCharacter* Caller) override;
	virtual bool IsInteractable_Implementation() const override;

	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void UpdateFromSave_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="State")
	bool GetMustShowWidget() const;
	
	
};
