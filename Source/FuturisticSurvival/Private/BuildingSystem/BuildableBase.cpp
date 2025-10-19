// developed by Neko


#include "BuildingSystem/BuildableBase.h"

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
	//TODO: Set the rest of data
}

void ABuildableBase::BeginPlay()
{
	Super::BeginPlay();
	
}


