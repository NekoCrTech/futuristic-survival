// developed by Neko


#include "BuildingSystem/BuildableBase.h"

#include "BuildingSystem/AttachmentPoint.h"
#include "BuildingSystem/BuildableBaseDataAsset.h"

ABuildableBase::ABuildableBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void ABuildableBase::SetData(const UBuildableBaseDataAsset* Data)
{
	Mesh->SetStaticMesh(Data->GetBuildingMesh());
	AttachedActors.Empty();
	const FActorSpawnParameters SpawnParameters;
	const TArray<FAttachmentPointData> AttachmentsData = Data->GetAttachments();
	for (const FAttachmentPointData Attachment : AttachmentsData)
	{
		AAttachmentPoint* AP = GetWorld()->SpawnActor<AAttachmentPoint>(AAttachmentPoint::StaticClass(),Attachment.Location,FRotator(0),SpawnParameters);
		AP->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
		AP->SetAcceptedToSnapParts(Attachment.PartsToSnap);
		AP->SetOwnerActor(this);
		AP->SetOwnerType(Data->GetType());
		AP->SetRotateMesh(Attachment.bRotate);
		AttachedActors.Add(AP);
	}
	//TODO: Set the rest of data
}

void ABuildableBase::BeginPlay()
{
	Super::BeginPlay();
	
}


