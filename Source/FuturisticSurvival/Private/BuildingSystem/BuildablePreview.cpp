// developed by Neko


#include "BuildingSystem/BuildablePreview.h"
#include "BuildingSystem/AttachmentPoint.h"
#include "Structs/AttachmentPointData.h"
#include "BuildingSystem/BuildableBaseDataAsset.h"

// Sets default values
ABuildablePreview::ABuildablePreview()
{
	PrimaryActorTick.bCanEverTick = true;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	PreviewMesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	PreviewMesh->SetupAttachment(Root);
	PreviewMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	PreviewMesh->SetGenerateOverlapEvents(true);
}

void ABuildablePreview::UpdateMaterial()
{
}

// Called when the game starts or when spawned
void ABuildablePreview::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildablePreview::Tick(float DeltaTime)
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

void ABuildablePreview::SetPreview(const UBuildableBaseDataAsset* Data)
{
	if (!PreviewMesh || !Data) return;

	PreviewMesh->SetStaticMesh(Data->GetBuildingMesh());
	PreviewMesh->SetMaterial(0, GoodMaterial);
	SetPartType(Data->GetType());
}

void ABuildablePreview::SnapPreviewToLocation(const FVector& TargetLocation)
{
	bSnapped=true;
	SetActorLocation(TargetLocation);
}




