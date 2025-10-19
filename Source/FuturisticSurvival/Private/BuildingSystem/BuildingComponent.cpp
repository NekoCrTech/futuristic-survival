// developed by Neko


#include "BuildingSystem/BuildingComponent.h"

#include "BuildingSystem/BuildableBase.h"
#include "BuildingSystem/BuildablePreview.h"
#include "Character/SurvPlayerCharacter.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	ASurvPlayerCharacter* tOwner = Cast<ASurvPlayerCharacter>(GetOwner());
	if (tOwner)
	{
		Owner = tOwner;
	}
	PlayerController = GetWorld()->GetFirstPlayerController();
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentPreview)
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			CurrentPreview->SetActorLocation(Hit.ImpactPoint);
			// Optional alignment:
			// CurrentPreview->SetActorRotation(Hit.ImpactNormal.Rotation());
		}
	}
}

bool UBuildingComponent::SelectBuilding(UBuildableBaseDataAsset* Data)
{
	// Check for cost
	/* if (!has enough resources)
	{
		return false;
	}
	*/
	
	Owner->ToggleBuildingModePlacement();
	bInPlacementMode = true;
	SpawnPreview(Data);
	return true;
}

void UBuildingComponent::PlaceBuilding()
{
	FTransform Trans = CurrentPreview->GetActorTransform();
	ABuildableBase* Buildable = GetWorld()->SpawnActor<ABuildableBase>(CurrentPreviewData->GetBuildable(), Trans);
	Buildable->SetData(CurrentPreviewData);
	// remove resources from inventory
}

void UBuildingComponent::CancelPlacement()
{
	if(CurrentPreview)
	{
		CurrentPreview->DestroyAttachments();
		CurrentPreview->Destroy();
	}
	CurrentPreviewData = nullptr;
	Owner->ToggleBuildingModePlacement();

	//TODO: Destroy Attachment Points
}

void UBuildingComponent::RotateBuilding(const bool& bRotateRight)
{
}

void UBuildingComponent::SpawnPreview(UBuildableBaseDataAsset* Data)
{
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		FVector SpawnLocation = HitResult.ImpactPoint;
		FRotator SpawnRotation = FRotator::ZeroRotator; // Or align with surface normal if needed
	}

	if (HitResult.bBlockingHit)
	{
		FVector SpawnLocation = HitResult.ImpactPoint;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentPreview = GetWorld()->SpawnActor<ABuildablePreview>(PreviewClass, SpawnLocation, FRotator::ZeroRotator,SpawnParams);
		CurrentPreview->SetPreview(Data);
		CurrentPreviewData = Data;
	}
}

void UBuildingComponent::AddToUnlockedBuildings(TArray<UBuildableBaseDataAsset*> BuildingsToUnlock)
{
	for (auto BuildingDataToUnlock : BuildingsToUnlock)
	{
		UnlockedBuildings.AddUnique(BuildingDataToUnlock);
	}
	
}

