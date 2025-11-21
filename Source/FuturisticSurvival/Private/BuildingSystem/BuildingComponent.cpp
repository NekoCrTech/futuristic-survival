// developed by Neko


#include "BuildingSystem/BuildingComponent.h"

#include "BuildingSystem/PlaceableActor.h"
#include "BuildingSystem/PlaceablePreview.h"
#include "BuildingSystem/PlacementControlInterface.h"
#include "BuildingSystem/SurvPlaceablesMenu.h"
#include "BuildingSystem/Placeables/SurvPlaceableBase.h"
#include "GameFramework/HUD.h"
#include "InventorySystem/InventoryComponent.h"
#include "UserInterface/HudInterface.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingComponent::InitializeBuildingComponent(UInventoryComponent* InventoryComponent)
{
	Inventory = InventoryComponent;
	if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		AHUD* HUD = PC->GetHUD();
		if (HUD && HUD->GetClass()->ImplementsInterface(UHudInterface::StaticClass()))
		{
			PlaceablesMenuWidget = IHudInterface::Execute_GetPlaceablesMenu(HUD);
			PlaceablesMenuWidget->UpdatePanels(UnlockedPlaceables);
			PlaceablesMenuWidget->OnPlaceableSelected.AddDynamic(this, &UBuildingComponent::SelectPlaceable);
		}
	}
}

void UBuildingComponent::SelectPlaceable(TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	if(Inventory->HasEnoughItems(PlaceableClass.GetDefaultObject()->GetCost()) == false)return;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	if (PC->GetClass()->ImplementsInterface(UPlacementControlInterface::StaticClass()))
	{
		IPlacementControlInterface::Execute_TogglePlacementMode(PC);
	}
	bInPlacementMode = true;
	SpawnPreview(PlaceableClass);
}

void UBuildingComponent::Place()
{
	FTransform Trans = CurrentPreview->GetActorTransform();
	APlaceableActor* Buildable = GetWorld()->SpawnActor<APlaceableActor>(CurrentPreviewClass.GetDefaultObject()->GetPlaceableClass(), Trans);
	Buildable->SetPlaceableClass(CurrentPreviewClass);
	//TODO: remove resources from inventory
}

void UBuildingComponent::CancelPlacement()
{
	if(CurrentPreview)
	{
		CurrentPreview->Destroy();
	}
	CurrentPreviewClass = nullptr;
	//Owner->ToggleBuildingModePlacement();
}

void UBuildingComponent::RotatePlacement(const bool& bRotateRight)
{
}

void UBuildingComponent::SpawnPreview(const TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		FVector SpawnLocation = HitResult.ImpactPoint;
		FRotator SpawnRotation = FRotator::ZeroRotator; // Or align with surface normal if needed

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentPreview = GetWorld()->SpawnActor<APlaceablePreview>(PlaceableClass.GetDefaultObject()->GetPreviewClass(), SpawnLocation, FRotator::ZeroRotator,SpawnParams);
		CurrentPreview->SetPreview(PlaceableClass);
		CurrentPreviewClass = PlaceableClass;
	}
}

void UBuildingComponent::AddToUnlockedPlaceables(TArray<TSubclassOf<USurvPlaceableBase>> PlaceablesToUnlock)
{
	for (auto PlaceableToUnlock : PlaceablesToUnlock)
	{
		UnlockedPlaceables.AddUnique(PlaceableToUnlock);
	}
}




