// developed by Neko


#include "Tools/RandomizedActor.h"

#include "Logger.h"


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
	
	int32 RandSeed = 0;
	switch (RandomizationVector)
	{
	case ERandomizedVector::X:
		RandSeed = floor(Transform.GetLocation().X);
		break;
	case ERandomizedVector::Y:
		RandSeed = floor(Transform.GetLocation().Y);
		break;
	case ERandomizedVector::Z:
		RandSeed = floor(Transform.GetLocation().Z);
		break;
	case ERandomizedVector::XY:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Y);
		break;
	case ERandomizedVector::XZ:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Z);
		break;
	case ERandomizedVector::YZ:
		RandSeed = floor(Transform.GetLocation().Y + Transform.GetLocation().Z);
		break;
	case ERandomizedVector::XYZ:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Y + Transform.GetLocation().Z);
		break;
	default:
		
		break;
	}
	
	FRandomStream RandStream;
	RandStream.Initialize(RandSeed);
	int32 idx = RandStream.RandRange(0, ActorOptions.Num() - 1);
	Mesh->SetStaticMesh(ActorOptions[idx]);
}


void ARandomizedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

