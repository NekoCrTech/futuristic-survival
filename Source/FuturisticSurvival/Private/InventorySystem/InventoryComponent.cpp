// developed by Neko


#include "InventorySystem/InventoryComponent.h"

#include "UserInterface/SurvHUD.h"
#include "InventorySystem/Items/ItemBase.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"

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
	InventoryWidget->UpdateContents();
	return true;
}

void UInventoryComponent::InitializeInventoryComponent()
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->IsPlayerControlled())
		{
			CreateInventoryWidget();
		}
	}
}

TMap<FIntPoint, FInventorySlotData> UInventoryComponent::GetInventoryContents_Implementation() const
{
	return Contents;
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
	if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
	{
		if (ASurvHUD* HUD = Cast<ASurvHUD>(PC->GetHUD()))
		{
			InventoryWidget = HUD->CreateInvWidget(GetOwner(), InventoryData, this);
		}
	}
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
