// developed by Neko


#include "Public/UserInterface/SurvHUD.h"
#include "InventorySystem/UserInterface/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Character/SurvPlayerCharacter.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/SurvPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/InventoryData.h"
#include "Structs/InventorySlotData.h"
#include "Player/PlayerWidget.h"

ASurvHUD::ASurvHUD()
{
}

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
	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(),PlayerWidgetClass);
	PlayerWidget->AddToViewport();
}

UInventoryWidget* ASurvHUD::CreateInvWidget(AActor* InOwner, const FInventoryData& InventoryData, UInventoryComponent* InventoryComponent)
{
	if (!InventoryData.InventoryWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateInvWidget failed: InventoryWidget class is null."));
		return nullptr;
	}
	UInventoryWidget* InventoryWidget = CreateWidget<UInventoryWidget>(GetOwningPlayerController(), InventoryData.InventoryWidget);
	InventoryWidget->SetWidgetOwner(InventoryComponent);
	InventoryWidget->SetInventoryData(InventoryData, InventoryComponent);
	
	if (Cast<ASurvPlayerCharacter>(InOwner))
	{
		PlayerInventoryWidget = InventoryWidget;
		OnPlayerInventoryCreated();
		return InventoryWidget;
	}
	OtherInventoryWidget = InventoryWidget;
	OnOtherInventoryCreated();
	return InventoryWidget;
}

void ASurvHUD::ToggleCharacterWindow()
{
	ASurvPlayerController* MyPC = Cast<ASurvPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	switch (PlayerWidget->ToggleCharacterWindow())
	{
	case ESlateVisibility::Visible:
		{
			PlayerWidget->SetRightPanel(PlayerInventoryWidget);
			PlayerInventoryWidget->SetIsOnScreen(true);
			PlayerInventoryWidget->UpdateContents();
			MyPC->SetMovementMappingContextEnabled(false);
			MyPC->SetShowMouseCursor(true);

			FInputModeGameAndUI InputGameAndUIMode;
			InputGameAndUIMode.SetHideCursorDuringCapture(false);
			InputGameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

			// ✅ Use GetCachedWidget() instead of TakeWidget()
			InputGameAndUIMode.SetWidgetToFocus(PlayerWidget->GetCachedWidget());

			MyPC->SetInputMode(InputGameAndUIMode);
			break;
		}
	case ESlateVisibility::Collapsed:
		{
			PlayerInventoryWidget->SetIsOnScreen(false);
			MyPC->SetMovementMappingContextEnabled(true);
			MyPC->SetShowMouseCursor(false);

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


void ASurvHUD::OnPlayerInventoryCreated_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"ASurvHUD::OnPlayerInventoryCreated - is not overwritten in blueprints");
}

void ASurvHUD::OnOtherInventoryCreated_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"ASurvHUD::OnOtherInventoryCreated - is not overwritten in blueprints");
}
