// developed by Neko


#include "BuildingSystem/BuildablePreview.h"
#include "BuildingSystem/AttachmentPoint.h"
#include "Structs/AttachmentPointData.h"
#include "BuildingSystem/BuildableBaseDataAsset.h"
#include "Components/SphereComponent.h"

// Sets default values
ABuildablePreview::ABuildablePreview()
{
	PrimaryActorTick.bCanEverTick = true;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	PreviewMesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	PreviewMesh->SetupAttachment(Root);
	CollisionSphere=CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisionSphere->SetHiddenInGame(false);

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
	PreviewMesh->SetStaticMesh(Data->GetBuildingMesh());
	PreviewMesh->SetMaterial(0,GoodMaterial);
	TArray<FAttachmentPointData> AttachmentsData = Data->GetAttachments();
	for (auto Attachment : AttachmentsData)
	{
		//UAttachmentPoint* AttachmentPoint = CreateDefaultSubobject<UAttachmentPoint>("Attachment Point");
		//AttachmentPoint->SetupAttachment()
	}
}

