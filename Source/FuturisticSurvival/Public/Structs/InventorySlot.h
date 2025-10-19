#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemBase.h"
#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemBase> ItemClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;

	FInventorySlot() = default;

	FInventorySlot(TSubclassOf<UItemBase> InItemClass, int32 InQuantity)
	{
		ItemClass = InItemClass;
		Quantity = InQuantity;
	}

	bool IsEmpty() const { return ItemClass == nullptr || Quantity <= 0; }
};
