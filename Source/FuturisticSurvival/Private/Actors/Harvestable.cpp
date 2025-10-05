// developed by Neko


#include "Actors/Harvestable.h"
#include "Actors/PickupActor.h"
#include "Structs/SaveActorData.h"


AHarvestable::AHarvestable()
{
	HarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HarvestableMesh->SetupAttachment(RootComponent);
	
	RemainingHarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Remaining Mesh"));
	RemainingHarvestableMesh->SetupAttachment(RootComponent);
	ChangeMeshCompVisibility(RemainingHarvestableMesh);
}

void AHarvestable::SetHarvestState()
{
	if(!bIsHarvested)
	{
		return;
	}
	HarvestableMesh->DestroyComponent();
	ChangeMeshCompVisibility(RemainingHarvestableMesh,true, ECollisionEnabled::QueryAndPhysics);
	MarkComponentsRenderStateDirty();
}

void AHarvestable::Harvest()
{
	bIsHarvested = true;
	SetHarvestState();
	SpawnPickups();
	OnHarvestedBP_Implementation();
}

void AHarvestable::SpawnPickups()
{
	if(!IsValid(PickUpActor))
	{
		return;
	}
	for( int i=0; i < DropSpawnQnt; i++ )
	{
		FVector HarvestableLoc = this->GetActorLocation();
		FTransform SpawnTrans = SpawnPickupsTransforms[i];
		SpawnTrans.SetLocation(SpawnTrans.GetLocation() + HarvestableLoc);
		APickupActor* Pickup = GetWorld()->SpawnActor<APickupActor>(PickUpActor, SpawnTrans);
		if (IsValid(Pickup))
		{
			Pickup->SetActorTransform(SpawnTrans);
			Pickup->SetWasSpawned(true);
		}
	}
}

float AHarvestable::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if(bIsHarvested || !DamageCauser->Tags.Contains(DamageCauserTag))
	{
		return 0.0f;
	}
	Health -= DamageAmount;
	if (Health > 0.0f)
	{
		return 0.0f;
	}
	Harvest();
	return 0.0f;
}

void AHarvestable::OnHarvestedBP_Implementation()
{
	OnHarvestedBP();
}

FSaveActorData AHarvestable::GetSaveData_Implementation()
{
	return FSaveActorData(GetActorTransform(),bWasSpawned,this->GetClass());
}

void AHarvestable::UpdateFromSave_Implementation()
{
	SetHarvestState();
}
