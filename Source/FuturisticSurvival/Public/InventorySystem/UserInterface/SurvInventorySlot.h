// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "SurvInventorySlot.generated.h"

class UTextBlock;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvInventorySlot : public USurvUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Survival|Inventory")
	void SetOwningInventory(class UInventoryComponent* Inventory) { OwningInventory = Inventory; }
	UFUNCTION(BlueprintCallable, Category = "Survival|Inventory")
	UInventoryComponent* GetOwningInventory() const { return OwningInventory; }
	UFUNCTION(BlueprintCallable, Category = "Survival|Inventory")
	FIntPoint GetItemSlotLocation() const { return SlotLocation; }
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), category = "Survival|Components")
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, category = "Survival|Inventory")
	FIntPoint SlotLocation;

	UPROPERTY(VisibleAnywhere, category = "Survival|Inventory")
	class UInventoryComponent* OwningInventory;
};
