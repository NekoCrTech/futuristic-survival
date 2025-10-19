// developed by Neko


#include "BuildingSystem/AttachmentPoint.h"

#include "Components/SphereComponent.h"

AAttachmentPoint::AAttachmentPoint()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AttachmentSphere = CreateDefaultSubobject<USphereComponent>("AttachmentSphere");
	RootComponent = AttachmentSphere;
	AttachmentSphere->InitSphereRadius(50.0f);
	AttachmentSphere ->SetHiddenInGame(false);

}

void AAttachmentPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

