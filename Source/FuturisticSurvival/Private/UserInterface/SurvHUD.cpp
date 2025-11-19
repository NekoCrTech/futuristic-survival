// developed by Neko


#include "Public/UserInterface/SurvHUD.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSystem/SurvPlaceablesMenu.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/SurvPlayerController.h"
#include "Kismet/GameplayStatics.h"
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

void ASurvHUD::ToggleCharacterWindow_Implementation(bool bUseOtherInventory)
{
	//TODO: Remove Player Controller reference from HUD 
	ASurvPlayerController* MyPC = Cast<ASurvPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
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
			MyPC->SetMovementMappingContextEnabled(false);
			MyPC->SetShowMouseCursor(true);

			FInputModeGameAndUI InputGameAndUIMode;
			InputGameAndUIMode.SetHideCursorDuringCapture(false);
			InputGameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
			InputGameAndUIMode.SetWidgetToFocus(PlayerWidget->GetCachedWidget());

			MyPC->SetInputMode(InputGameAndUIMode);
			break;
		}
	case ESlateVisibility::Collapsed:
		{
			PlayerWidget->PlayerInventoryWidget->SetIsOnScreen(false);
			MyPC->SetMovementMappingContextEnabled(true);
			MyPC->SetShowMouseCursor(false);
			
			if(OtherInventoryWidget)
			{
				PlayerWidget->CloseOtherInventory();
				OtherInventoryWidget=nullptr;
			}

			FInputModeGameOnly InputGameOnlyMode;
			MyPC->SetInputMode(InputGameOnlyMode);
			break;
		}
	default:
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
				TEXT("ASurvHUD::ToggleCharacterWindow - CharacterWindow visibility is not Visible or Collapsed"));
			break;
		}
	}
}

void ASurvHUD::TogglePlacementWindow_Implementation()
{
	switch(PlayerWidget->PlaceablesMenu->GetVisibility()) {
	case ESlateVisibility::Visible:
		PlayerWidget->PlaceablesMenu->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::Collapsed:
		PlayerWidget->PlaceablesMenu->SetVisibility(ESlateVisibility::Visible);
		break;
	case ESlateVisibility::Hidden:
		break;
	case ESlateVisibility::HitTestInvisible:
		break;
	case ESlateVisibility::SelfHitTestInvisible:
		break;
	}

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

