// developed by Neko
// TODO: Rework Stacking when pickup;

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Save/SaveActorInterface.h"
#include "Structs/InventorySlot.h"
#include "Structs/ItemUiData.h"
#include "InventoryComponent.generated.h"

class ASurvCharacter;
class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UInventoryComponent : public UActorComponent, public ISaveActorInterface
{
	GENERATED_BODY()


public:	
	UInventoryComponent();

	bool AddItemToInventory(TSubclassOf<UItemBase> Item);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	float MaxWeight = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	int32 Capacity = -1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	int32 Columns = 10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	float CurrentWeight = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true")) //TODO: make it EditDefaultOnly
	TMap<FIntPoint, FInventorySlot> Contents;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	ASurvCharacter* Owner;

	
	bool AddOneToStack(const TSubclassOf<UItemBase> ItemToAdd);
	FIntPoint GetFirstEmptySlot() const;
	TSubclassOf<UItemBase> GetItemAtPosition(const FIntPoint& Position) const;

	


	
};
