// developed by Neko
// TODO: Rework Stacking when pickup;

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Structs/InventoryData.h"
#include "Structs/InventorySlotData.h"
#include "Structs/ItemUiData.h"
#include "Save/SaveActorInterface.h"
#include "InventoryInterface.h"
#include "InventoryComponent.generated.h"

class UInventoryWidget;
class ASurvCharacter;
class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UInventoryComponent : public UActorComponent, public ISaveActorInterface, public IInventoryInterface
{
	GENERATED_BODY()


public:	
	UInventoryComponent();

	bool AddItemToInventory(TSubclassOf<UItemBase> Item);

	void InitializeInventoryComponent();
	
	virtual TMap<FIntPoint, FInventorySlotData>GetInventoryContents_Implementation() const override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData", Meta = (AllowPrivateAccess = "true"))
	FInventoryData InventoryData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData", Meta = (AllowPrivateAccess = "true"))
	float CurrentWeight = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData", Meta = (AllowPrivateAccess = "true")) //TODO: make it EditDefaultOnly
	TMap<FIntPoint, FInventorySlotData> Contents;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Survival|InventoryData", Meta = (AllowPrivateAccess = "true"))
	UInventoryWidget* InventoryWidget;
	
	bool AddOneToStack(const TSubclassOf<UItemBase> ItemToAdd);
	FIntPoint GetFirstEmptySlot() const;
	TSubclassOf<UItemBase> GetItemAtPosition(const FIntPoint& Position) const;

	void CreateInventoryWidget();
};
