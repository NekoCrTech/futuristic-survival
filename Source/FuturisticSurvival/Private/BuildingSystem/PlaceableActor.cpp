// developed by Neko


#include "BuildingSystem/PlaceableActor.h"

#include "BuildingSystem/AttachmentPoint.h"
#include "BuildingSystem/BuildableBaseDataAsset.h"

APlaceableActor::APlaceableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void APlaceableActor::SetPlaceableClass(TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	// Mesh->SetStaticMesh(PlaceableClass->GetBuildingMesh());
	// AttachedActors.Empty();
	// const FActorSpawnParameters SpawnParameters;
	// const TArray<FAttachmentPointData> AttachmentsData = PlaceableClass->GetAttachments();
	// for (const FAttachmentPointData Attachment : AttachmentsData)
	// {
	// 	AAttachmentPoint* AP = GetWorld()->SpawnActor<AAttachmentPoint>(AAttachmentPoint::StaticClass(),Attachment.Location,FRotator(0),SpawnParameters);
	// 	AP->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
	// 	AP->SetAcceptedToSnapParts(Attachment.PartsToSnap);
	// 	AP->SetOwnerActor(this);
	// 	AP->SetOwnerType(PlaceableClass->GetType());
	// 	AP->SetRotateMesh(Attachment.bRotate);
	// 	AttachedActors.Add(AP);
	// }
	// //TODO: Set the rest of data
}

void APlaceableActor::BeginPlay()
{
	Super::BeginPlay();
	
}


