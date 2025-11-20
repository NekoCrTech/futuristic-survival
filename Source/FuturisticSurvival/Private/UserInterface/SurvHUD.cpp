// developed by Neko


#include "Public/UserInterface/SurvHUD.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSystem/SurvPlaceablesMenu.h"
#include "InventorySystem/InventoryComponent.h"
#include "Structs/InventoryData.h"
#include "Player/UserInterface/PlayerHud.h"

void ASurvHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ASurvHUD::InitializeHUD()
{
	if(!IsValid(PlayerWidgetClass))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"ASurvHUD::InitializeHUD - PlayerWidgetClass is not valid");
		return;
	}
	PlayerWidget = CreateWidget<UPlayerHud>(GetWorld(),PlayerWidgetClass);
	PlayerWidget->AddToViewport();
	OnHudCreated.Broadcast();
}

ESlateVisibility ASurvHUD::ToggleCharacterWindow_Implementation(bool bUseOtherInventory)
{
	switch (PlayerWidget->ToggleCharacterWindow())
	{
	case ESlateVisibility::Visible:
		{
			if(bUseOtherInventory)
			{
				PlayerWidget->SetOtherInventory(OtherInventoryWidget);
			}
			PlayerWidget->PlayerInventoryWidget->SetIsOnScreen(true);
			PlayerWidget->PlayerInventoryWidget->UpdateContents();
			return ESlateVisibility::Visible;
		}
	case ESlateVisibility::Collapsed:
		{
			PlayerWidget->PlayerInventoryWidget->SetIsOnScreen(false);
			
			if(OtherInventoryWidget)
			{
				PlayerWidget->CloseOtherInventory();
				OtherInventoryWidget=nullptr;
			}
			return ESlateVisibility::Collapsed;
		}
	default:
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
				TEXT("ASurvHUD::ToggleCharacterWindow - CharacterWindow visibility is not Visible or Collapsed"));
			return ESlateVisibility::Collapsed;
		}
	}
}

ESlateVisibility ASurvHUD::TogglePlacementWindow_Implementation()
{
	if(PlayerWidget->PlaceablesMenu->GetVisibility()!=ESlateVisibility::Visible)
	{
		PlayerWidget->PlaceablesMenu->SetVisibility(ESlateVisibility::Visible);
		return ESlateVisibility::Visible;
		
	}
	PlayerWidget->PlaceablesMenu->SetVisibility(ESlateVisibility::Collapsed);
	return ESlateVisibility::Collapsed;
}

UInventoryWidget* ASurvHUD::CreateInventoryWidget_Implementation(AActor* InOwner, const FInventoryData& InventoryData)
{
	if (GetOwningPlayerController()->GetPawn() == InOwner)
	{
		return PlayerWidget->PlayerInventoryWidget;
	}
	UInventoryWidget* InventoryWidget = CreateWidget<UInventoryWidget>(GetOwningPlayerController(), InventoryData.InventoryWidget);
	OtherInventoryWidget = InventoryWidget;
	return InventoryWidget;
}

USurvPlaceablesMenu* ASurvHUD::GetPlaceablesMenu_Implementation()
{
	return PlayerWidget->PlaceablesMenu;
}

TSharedPtr<SWidget> ASurvHUD::GetCachedPlayerWidget() const
{
	return PlayerWidget->GetCachedWidget();
}

TSharedPtr<SWidget> ASurvHUD::GetCachedPlacementWidget() const
{
	return PlayerWidget->PlaceablesMenu->GetCachedWidget();
}

