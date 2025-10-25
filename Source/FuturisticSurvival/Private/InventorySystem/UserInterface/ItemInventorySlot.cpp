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
	FItemUIData UIData = Item.GetDefaultObject()->GetItemUIData(Location);
	
	ItemIcon->SetBrushFromTexture(UIData.ItemIcon);
	ItemBorder->SetBrushColor(UIData.ItemQualityColor);
	if (Quantity > 1)
	{
		ItemQuantity->SetText(FText::AsNumber(Quantity));
		ItemQuantity->SetVisibility(ESlateVisibility::Visible);
	}
	
}
