// developed by Neko


#include "Tools/RandomizedActor.h"

#include "Logger.h"
#include "SurvUtils.h"


ARandomizedActor::ARandomizedActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void ARandomizedActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ActorOptions.Num() <= 0)
	{
		Logger::GetInstance()->AddMessage("ARandomizedActor::OnConstruction - ActorOptions is empty", EL_ERROR);
		return;
	}

	if (bOverrideRandomization && OverrideIndex <= ActorOptions.Num())
	{
		Mesh->SetStaticMesh(ActorOptions[OverrideIndex]);
		return;
	}
	
	int32 RandSeed = RandomIntFromVector(RandomizationVector, Transform.GetLocation());
	
	FRandomStream RandStream;
	RandStream.Initialize(RandSeed);
	int32 idx = RandStream.RandRange(0, ActorOptions.Num() - 1);
	Mesh->SetStaticMesh(ActorOptions[idx]);
}


void ARandomizedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

