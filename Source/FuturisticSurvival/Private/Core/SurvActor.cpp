// developed by Neko


#include "Core/SurvActor.h"
#include "Structs/SaveActorData.h"


ASurvActor::ASurvActor()
{
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
 	
	PrimaryActorTick.bCanEverTick = true;

	SaveID = FGuid::NewGuid();

}

void ASurvActor::BeginPlay()
{
	Super::BeginPlay();

	if (!SaveID.IsValid())
	{
		SaveID = FGuid::NewGuid();
	}
	
}

void ASurvActor::ChangeMeshCompVisibility(UStaticMeshComponent* MeshComp, bool Visible, ECollisionEnabled::Type NewCollision)
{
	if (!MeshComp){return;}
	
	MeshComp->SetHiddenInGame(!Visible);
	MeshComp->SetCollisionEnabled(NewCollision);
	MarkComponentsRenderStateDirty();
}

void ASurvActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FGuid ASurvActor::GetActorSaveID_Implementation()
{
	return SaveID;
}

void ASurvActor::SetActorGUID_Implementation(const FGuid& NewGiud)
{
	if (!SaveID.IsValid())
	{
		SaveID.Invalidate();
	}
	SaveID = NewGiud;
}

FSaveActorData ASurvActor::GetSaveData_Implementation()
{
	return FSaveActorData(GetActorTransform(),bWasSpawned, GetClass());
}

void ASurvActor::UpdateFromSave_Implementation()
{
	
}

void ASurvActor::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}

