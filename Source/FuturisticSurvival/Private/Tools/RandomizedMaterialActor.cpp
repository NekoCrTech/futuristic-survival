// developed by Neko


#include "Tools/RandomizedMaterialActor.h"

#include "SurvUtils.h"


ARandomizedMaterialActor::ARandomizedMaterialActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void ARandomizedMaterialActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!bRandomize || RandomizedMaterials.Num() <= 0)
	{
		return;
	}

	int32 RandSeed = RandomIntFromVector(RandomizationVector, Transform.GetLocation());
	
	FRandomStream RandStream;
	RandStream.Initialize(RandSeed);
	TArray<int> Keys;
	RandomizedMaterials.GetKeys(Keys);
	for (int32 i = Keys[0]; i < RandomizedMaterials.Num(); i++)
	{
		if (RandomizedMaterials[i].Materials.Num() <= 0)
		{
			continue;
		}
		
		int32 idx = RandStream.RandRange(0,RandomizedMaterials[i].Materials.Num()-1);
		Mesh->SetMaterial(i, RandomizedMaterials[i].Materials[idx]);
	}	
}

void ARandomizedMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	
}


