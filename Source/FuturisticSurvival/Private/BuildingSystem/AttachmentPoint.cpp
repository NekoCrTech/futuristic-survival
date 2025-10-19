// developed by Neko


#include "BuildingSystem/AttachmentPoint.h"

#include "Components/SphereComponent.h"

UAttachmentPoint::UAttachmentPoint()
{
	PrimaryComponentTick.bCanEverTick = false;

	AttachmentSphere=CreateDefaultSubobject<USphereComponent>("Attachment Mesh");
	AttachmentSphere->SetHiddenInGame(false);

}


// Called when the game starts
void UAttachmentPoint::BeginPlay()
{
	Super::BeginPlay();

}


