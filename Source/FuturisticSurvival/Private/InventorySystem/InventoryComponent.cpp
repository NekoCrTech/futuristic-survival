// developed by Neko


#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/Items/ItemBase.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"
#include "GameFramework/HUD.h"
#include "UserInterface/HudInterface.h"

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
		
		Contents.Add(GetFirstEmptySlot(), FInventorySlotData(Item,1));
		--Remaining;
	}
	if(IsValid(InventoryWidget))
	{
		InventoryWidget->UpdateContents();
	}
	return true;
}

bool UInventoryComponent::HasEnoughItems(const TMap<TSubclassOf<UItemBase>, int32>& Items) const
{
	for (const TPair<TSubclassOf<UItemBase>, int32>& Pair : Items)
	{
		TSubclassOf<UItemBase> ItemClass = Pair.Key;
		int32 Quantity = Pair.Value;

		if (GetQuantityOfItem(ItemClass) < Quantity) return false;
	}
	return true;
}

bool UInventoryComponent::RemoveItems(const TArray<FInventorySlotData>& ItemsToRemove)
{
	//if (!HasEnoughItems(ItemsToRemove))	return false;

	for (const FInventorySlotData& ToRemove : ItemsToRemove)
	{
		int32 RemainingToRemove = ToRemove.Quantity;

		// Loop through all slots in Contents
		for (auto& Elem : Contents)
		{
			FInventorySlotData& SlotData = Elem.Value;

			// Skip slots that don't contain the same item type
			if (SlotData.ItemClass != ToRemove.ItemClass)
				continue;

			// Determine how much to remove from this stack
			const int32 RemoveAmount = FMath::Min(SlotData.Quantity, RemainingToRemove);
			SlotData.Quantity -= RemoveAmount;
			RemainingToRemove -= RemoveAmount;

			// If the stack is empty, clear it
			if (SlotData.Quantity <= 0)
			{
				SlotData.ItemClass = nullptr;
				SlotData.Quantity = 0;
			}

			// If we’ve removed everything needed, break out early
			if (RemainingToRemove <= 0)
				break;
		}
	}

	if(IsValid(InventoryWidget))
	{
		InventoryWidget->UpdateContents();
	}
	return true;
}

bool UInventoryComponent::RemoveSingleItem(const TSubclassOf<UItemBase>& ItemToRemove)
{
	if (!ItemToRemove) return false;

	for (auto& Pair : Contents)
	{
		FInventorySlotData& SlotData = Pair.Value;

		if (SlotData.ItemClass == ItemToRemove && SlotData.Quantity > 0)
		{
			// Remove one
			SlotData.Quantity--;

			// Remove slot if empty
			if (SlotData.Quantity <= 0)
			{
				Contents.Remove(Pair.Key);
			}

			if(IsValid(InventoryWidget))
			{
				InventoryWidget->UpdateContents();
			}

			return true;
		}
	}

	// Item not found
	return false;
}

void UInventoryComponent::TransferSlots(const FIntPoint& SourceLocation, UInventoryComponent* SourceInventory, const FIntPoint& TargetLocation)
{
	//TODO: Fix Stacking.
	if (!SourceInventory) return;
    if (SourceInventory->IsOutOfBounds(SourceLocation)) return;
    // Ignore same-slot moves
    if (SourceInventory == this && SourceLocation == TargetLocation) return;

    FInventorySlotData* SourceSlotPtr = SourceInventory->Contents.Find(SourceLocation);
    if (!SourceSlotPtr) return;

    const FInventorySlotData SourceSlotData = *SourceSlotPtr;

    if (IsOutOfBounds(TargetLocation))
    {
        // TODO: Drop logic
        return;
    }

    // --- Same inventory move ---
    if (SourceInventory == this)
    {
        // Moving inside the same map
        FInventorySlotData* TargetSlotPtr = Contents.Find(TargetLocation);

        if (!TargetSlotPtr)
        {
            // Move: Add new slot, then remove old
            Contents.Add(TargetLocation, SourceSlotData);
            Contents.Remove(SourceLocation);
        }
        else if (TargetSlotPtr->ItemClass == SourceSlotData.ItemClass)
        {
            // Stack
            TargetSlotPtr->Quantity += SourceSlotData.Quantity;
            Contents.Remove(SourceLocation);
        }
        else
        {
            // Swap
            FInventorySlotData OldTarget = *TargetSlotPtr;
            Contents.Add(TargetLocation, SourceSlotData);
            Contents.Add(SourceLocation, OldTarget);
        }
    }
    // --- Between two different inventories ---
    else
    {
        FInventorySlotData* TargetSlotPtr = Contents.Find(TargetLocation);

        if (!TargetSlotPtr)
        {
            // Move from source to target
            Contents.Add(TargetLocation, SourceSlotData);
            SourceInventory->Contents.Remove(SourceLocation);
        }
        else if (TargetSlotPtr->ItemClass == SourceSlotData.ItemClass)
        {
            // Stack
            TargetSlotPtr->Quantity += SourceSlotData.Quantity;
            SourceInventory->Contents.Remove(SourceLocation);
        }
        else
        {
            // Swap
            FInventorySlotData OldTarget = *TargetSlotPtr;
            SourceInventory->Contents.Add(SourceLocation, OldTarget);
            Contents.Add(TargetLocation, SourceSlotData);
        }
    }

    // --- Update widgets ---
    if (IsValid(InventoryWidget))
        UpdateInventoryWidget();
    if (IsValid(SourceInventory->InventoryWidget) && SourceInventory != this)
        SourceInventory->InventoryWidget->UpdateContents();
}

TMap<FIntPoint, FInventorySlotData> UInventoryComponent::GetInventoryContents_Implementation() const
{
	return Contents;
}

TArray<FInventorySlotData> UInventoryComponent::GetMissingItems(const TArray<FInventorySlotData>& RequiredItems) const
{
	TArray<FInventorySlotData> MissingItems;

	for (const FInventorySlotData& Required : RequiredItems)
	{
		const int32 CurrentQuantity = GetQuantityOfItem(Required.ItemClass);

		if (CurrentQuantity < Required.Quantity)
		{
			FInventorySlotData MissingData;
			MissingData.ItemClass = Required.ItemClass;
			MissingData.Quantity = Required.Quantity - CurrentQuantity;
			MissingItems.Add(MissingData);
		}
	}

	return MissingItems;
}

// Find the first empty slot (infinite grid)
FIntPoint UInventoryComponent::GetFirstEmptySlot() const
{
	int32 Row = 0;

	while (true)
	{
		for (int32 Col = 0; Col < InventoryData.Columns; ++Col)
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
	if (const FInventorySlotData* Found = Contents.Find(Position))
	{
		return Found->ItemClass;
	}
	return nullptr;
}

void UInventoryComponent::CreateInventoryWidget()
{
	if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		AHUD* HUD = PC->GetHUD();
		if (HUD && HUD->GetClass()->ImplementsInterface(UHudInterface::StaticClass()))
		{
			InventoryWidget = IHudInterface::Execute_CreateInventoryWidget(HUD,GetOwner(),InventoryData);
			InventoryWidget->SetWidgetOwner(this);
			InventoryWidget->SetInventoryData(InventoryData,this);
		}
	}
}

void UInventoryComponent::UpdateInventoryWidget()
{
	InventoryWidget->UpdateContents();
}

int32 UInventoryComponent::GetQuantityOfItem(const TSubclassOf<UItemBase>& ItemClass) const
{
	if (!ItemClass) return 0;
	int32 TotalQuantity = 0;

	for (const TPair<FIntPoint, FInventorySlotData>& Entry : Contents)
	{
		const FInventorySlotData& SlotData = Entry.Value;

		if (SlotData.ItemClass == ItemClass)
		{
			TotalQuantity += SlotData.Quantity;
		}
	}

	return TotalQuantity;
}

bool UInventoryComponent::IsOutOfBounds(const FIntPoint& Position) const
{
	return false;
}

// Try to add +1 to an existing stack of the same item
bool UInventoryComponent::AddOneToStack(TSubclassOf<UItemBase> Item)
{
	const UItemBase* DefaultItem = Item.GetDefaultObject();
	if (!DefaultItem) return false;
	
	const int32 MaxStack = DefaultItem->GetStackSize();

	for (auto& Pair : Contents)
	{
		FInventorySlotData& Slot = Pair.Value;

		if (Slot.ItemClass == Item && Slot.Quantity < MaxStack)
		{
			++Slot.Quantity;
			return true;
		}
	}
	return false;
}
