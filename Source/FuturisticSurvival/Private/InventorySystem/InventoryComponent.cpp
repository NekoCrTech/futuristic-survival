// developed by Neko


#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/Items/ItemBase.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Add an item class to inventory (supports stacking)
bool UInventoryComponent::AddItemToInventory(TSubclassOf<UItemBase> Item)
{
	if (!Item) return false;

	const UItemBase* DefaultItem = Item.GetDefaultObject();
	int32 Remaining = DefaultItem->GetCurrentStack();

	while (Remaining > 0)
	{
		// Try to add to an existing stack
		if (AddOneToStack(Item))
		{
			--Remaining;
			continue;
		}
		
		Contents.Add(GetFirstEmptySlot(), FInventorySlot(Item,1));
		--Remaining;
	}

	return true;
}

// Find the first empty slot (infinite grid)
FIntPoint UInventoryComponent::GetFirstEmptySlot() const
{
	int32 Row = 0;

	while (true)
	{
		for (int32 Col = 0; Col < Columns; ++Col)
		{
			const FIntPoint Position(Col, Row);
			if (!Contents.Contains(Position))
			{
				return Position;
			}
		}
		++Row;
	}
}

// Get the item class stored at a specific slot
TSubclassOf<UItemBase> UInventoryComponent::GetItemAtPosition(const FIntPoint& Position) const
{
	if (const FInventorySlot* Found = Contents.Find(Position))
	{
		return Found->ItemClass;
	}
	return nullptr;
}

// Try to add +1 to an existing stack of the same item
bool UInventoryComponent::AddOneToStack(TSubclassOf<UItemBase> Item)
{
	const UItemBase* DefaultItem = Item.GetDefaultObject();
	if (!DefaultItem) return false;
	
	const int32 MaxStack = DefaultItem->GetStackSize();

	for (auto& Pair : Contents)
	{
		FInventorySlot& Slot = Pair.Value;

		if (Slot.ItemClass == Item && Slot.Quantity < MaxStack)
		{
			++Slot.Quantity;
			return true;
		}
	}
	return false;
}
