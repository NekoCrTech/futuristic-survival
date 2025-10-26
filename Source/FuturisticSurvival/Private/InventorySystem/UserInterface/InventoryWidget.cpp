// developed by Neko


#include "InventorySystem/UserInterface/InventoryWidget.h"
#include "Structs/InventorySlotData.h"
#include "InventorySystem/InventoryInterface.h"


void UInventoryWidget::UpdateContents()
{
	if (!WidgetOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidget has no owner set."));
		return;
	}
	if (WidgetOwner->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()) && GetIsOnScreen())
	{
		TMap<FIntPoint, FInventorySlotData> Contents = IInventoryInterface::Execute_GetInventoryContents(WidgetOwner);
		OnInventoryUpdate(Contents);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetOwner does not implement IInventoryInterface."));
	}
}

void UInventoryWidget::OnInventoryUpdate_Implementation(const TMap<FIntPoint, FInventorySlotData>& Contents)
{
	UE_LOG(LogTemp, Warning, TEXT("UpgradeGrid is not implemented in Blueprints"));
}


void UInventoryWidget::SetInventoryData(const FInventoryData& InventoryDataToSet)
{
	InventoryData = InventoryDataToSet;
	UpdateContents();
}
