// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/UserInterface/SurvInventorySlot.h"
#include "Structs/InventorySlotData.h"
#include "ItemInventorySlot.generated.h"

class UItemBase;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UItemInventorySlot : public USurvInventorySlot
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Survival|InventorySystem")
	void SetItem(const FInventorySlotData& InventorySlotData,const FIntPoint& Location);

	UFUNCTION(BlueprintCallable)
	FItemUIData GetItemUIData() const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UItemBase> GetItemClass() const { return Item; }

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Survival|Components")
	UImage* ItemIcon;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Survival|Components")
	UTextBlock* ItemQuantity;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Survival|InventorySlot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemBase> Item;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Survival|InventorySlot", meta = (AllowPrivateAccess = "true"))
	int32 Quantity;
};
