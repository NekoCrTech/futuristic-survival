// developed by Neko


#include "Player/UserInterface/PlayerHud.h"

#include "Components/Overlay.h"

ESlateVisibility UPlayerHud::ToggleCharacterWindow(bool bUseOtherInventory)
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
