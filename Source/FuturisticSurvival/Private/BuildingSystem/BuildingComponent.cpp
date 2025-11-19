// developed by Neko


#include "BuildingSystem/BuildingComponent.h"

#include "BuildingSystem/PlaceableActor.h"
#include "BuildingSystem/BuildablePreview.h"
#include "BuildingSystem/SurvPlaceablesMenu.h"
#include "BuildingSystem/Placeables/SurvPlaceableBase.h"
#include "GameFramework/HUD.h"
#include "UserInterface/HudInterface.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingComponent::InitializeBuildingComponent()
{
	if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		AHUD* HUD = PC->GetHUD();
		if (HUD && HUD->GetClass()->ImplementsInterface(UHudInterface::StaticClass()))
		{
			PlaceablesMenuWidget = IHudInterface::Execute_GetPlaceablesMenu(HUD);
			PlaceablesMenuWidget->UpdatePanels(UnlockedPlaceables);
		}
	}
}

bool UBuildingComponent::SelectPlaceable(TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	// Check for cost
	/* if (!has enough resources)
	{
		return false;
	}
	*/
	
	//Owner->ToggleBuildingModePlacement();
	bInPlacementMode = true;
	SpawnPreview(PlaceableClass);
	return true;
}

void UBuildingComponent::Place()
{
	FTransform Trans = CurrentPreview->GetActorTransform();
	APlaceableActor* Buildable = GetWorld()->SpawnActor<APlaceableActor>(CurrentPreviewClass.GetDefaultObject()->GetPlaceableClass(), Trans);
	Buildable->SetPlaceableClass(CurrentPreviewClass);
	// remove resources from inventory
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

		CurrentPreview = GetWorld()->SpawnActor<ABuildablePreview>(PreviewClass, SpawnLocation, FRotator::ZeroRotator,SpawnParams);
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




