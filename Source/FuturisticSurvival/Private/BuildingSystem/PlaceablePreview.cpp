// developed by Neko


#include "BuildingSystem/PlaceablePreview.h"
#include "BuildingSystem/AttachmentPoint.h"
#include "Structs/AttachmentPointData.h"
#include "BuildingSystem/Placeables/SurvPlaceableBase.h"

class USurvPlaceableBase;
// Sets default values
APlaceablePreview::APlaceablePreview()
{
	PrimaryActorTick.bCanEverTick = true;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	PreviewMesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	PreviewMesh->SetupAttachment(Root);
	PreviewMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	PreviewMesh->SetGenerateOverlapEvents(true);
}

void APlaceablePreview::UpdateMaterial()
{
}

// Called when the game starts or when spawned
void APlaceablePreview::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaceablePreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	
	if (!bSnapped)
	{
		if (Hit.bBlockingHit)
		{
			SetActorLocation(Hit.ImpactPoint);
		}
	}
	if (!Hit.bBlockingHit || FVector::Dist(Hit.ImpactPoint, GetActorLocation()) > 150.0f)
	{
		bSnapped = false;
	}
	
}

void APlaceablePreview::SetPreview(TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	
	PreviewMesh->SetStaticMesh(PlaceableClass.GetDefaultObject()->GetPlaceableMesh());
	PreviewMesh->SetMaterial(0, GoodMaterial);
	//SetPartType(Data->GetType());
}

void APlaceablePreview::SnapPreviewToLocation(const FVector& TargetLocation)
{
	bSnapped=true;
	SetActorLocation(TargetLocation);
}




