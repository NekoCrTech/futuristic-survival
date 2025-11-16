// developed by Neko


#include "Player/UserInterface/PlayerHud.h"
#include "Components/Overlay.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"

void UPlayerHud::SetOtherInventory(UInventoryWidget* OtherInventoryWidget)
{
	OtherInventoryOverlay->AddChildToOverlay(OtherInventoryWidget);
	OtherInventoryOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHud::CloseOtherInventory()
{
	OtherInventoryOverlay->ClearChildren();
	OtherInventoryOverlay->SetVisibility(ESlateVisibility::Collapsed);
}

ESlateVisibility UPlayerHud::ToggleCharacterWindow()
{
	switch(CharacterMenuOverlay->GetVisibility())
	{
	case ESlateVisibility::Visible:
		CharacterMenuOverlay->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::Collapsed:
		CharacterMenuOverlay->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"UPlayerWidget::ToggleCharacterWindow - CharacterWindow visibility is not Visible or Collapsed");
		break;
	}
	return CharacterMenuOverlay->GetVisibility();
}
