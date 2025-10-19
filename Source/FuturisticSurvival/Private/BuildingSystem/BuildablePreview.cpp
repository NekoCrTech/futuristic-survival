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

}

void ABuildablePreview::SetPreview(const UBuildableBaseDataAsset* Data)
{
	if (!PreviewMesh || !Data) return;

	PreviewMesh->SetStaticMesh(Data->GetBuildingMesh());
	PreviewMesh->SetMaterial(0, GoodMaterial);
	AttachedActors.Empty();
	const FActorSpawnParameters SpawnParameters;
	const TArray<FAttachmentPointData> AttachmentsData = Data->GetAttachments();
	for (const FAttachmentPointData Attachment : AttachmentsData)
	{
		AAttachmentPoint* AP = GetWorld()->SpawnActor<AAttachmentPoint>(AAttachmentPoint::StaticClass(),Attachment.Position,FRotator(0),SpawnParameters);
		//AP->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		AP->AttachToComponent(PreviewMesh,FAttachmentTransformRules::KeepRelativeTransform);
		AP->SetAcceptedToSnapParts(Attachment.PartsToSnap);
		AP->SetOwnerActor(this);
		AP->SetOwnerType(Data->GetType());
		AttachedActors.Add(AP);
	}

}

void ABuildablePreview::DestroyAttachments()
{
	for (AActor* Actor : AttachedActors)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}
}




