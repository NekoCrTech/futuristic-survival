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

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Survival|Components")
	UImage* ItemIcon;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Survival|Components")
	UTextBlock* ItemQuantity;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|InventorySlot", meta = (AllowPrivateAccess = "true")) // TODO: Revert to VisibleAnywhere
	TSubclassOf<UItemBase> Item;
	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Survival|InventorySlot", meta = (AllowPrivateAccess = "true")) // TODO: Revert to VisibleAnywhere
	int32 Quantity;
};
