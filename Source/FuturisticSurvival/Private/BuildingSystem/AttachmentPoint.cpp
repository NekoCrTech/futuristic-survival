// developed by Neko


#include "BuildingSystem/AttachmentPoint.h"

#include "BuildingSystem/BuildablePreview.h"
#include "Components/SphereComponent.h"

AAttachmentPoint::AAttachmentPoint()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AttachmentSphere = CreateDefaultSubobject<USphereComponent>("AttachmentSphere");
	RootComponent = AttachmentSphere;
	AttachmentSphere->InitSphereRadius(25.0f);
	AttachmentSphere->SetHiddenInGame(false);
	AttachmentSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractionTriggerOverlapBegin);
	AttachmentSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractionTriggerOverlapEnd);

}

void AAttachmentPoint::OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bAttachmentIsActive) return;
	ABuildablePreview* BuildablePreview = Cast<ABuildablePreview>(OtherActor);
	if (!IsValid(BuildablePreview)) return;
	if (!AcceptedToSnapParts.Contains(BuildablePreview->GetPartType())) return;
	BuildablePreview->SnapPreviewToLocation(GetActorLocation());
	if(bRotateMesh && !BuildablePreview->IsRotated())
	{
		BuildablePreview->SetActorRotation(FRotator(0, 90, 0));
		BuildablePreview->SetIsRotated(true);
		return;
	}
	if (!bRotateMesh && BuildablePreview->IsRotated())
	{
		BuildablePreview->SetActorRotation(FRotator(0, 0, 0));
		BuildablePreview->SetIsRotated(false);
		return;
	}
}

void AAttachmentPoint::OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void AAttachmentPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

