// developed by Neko


#include "InventorySystem/UserInterface/ItemInventorySlot.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventorySystem/Items/ItemBase.h"

void UItemInventorySlot::SetItem(const FInventorySlotData& InventorySlotData,const FIntPoint& Location)
{
	Item = InventorySlotData.ItemClass;
	Quantity = InventorySlotData.Quantity;

	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetItem: ItemClass is null at location %s"), *Location.ToString());
		return;
	}

	UItemBase* DefaultItem = Item.GetDefaultObject();
	if (!DefaultItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetItem: GetDefaultObject() returned null for item %s"), *Item->GetName());
		return;
	}

	SlotLocation = Location;
	FItemUIData UIData = DefaultItem->GetItemUIData(Location);

	if (ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(UIData.ItemIcon);
	}

	if (ItemBorder)
	{
		ItemBorder->SetBrushColor(UIData.ItemQualityColor);
	}

	if (ItemQuantity)
	{
		if (Quantity > 1)
		{
			ItemQuantity->SetText(FText::AsNumber(Quantity));
			ItemQuantity->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

FItemUIData UItemInventorySlot::GetItemUIData() const
{
	return Item ? Item.GetDefaultObject()->GetItemUIData(SlotLocation) : FItemUIData();
}
