// developed by Neko


#include "Actors/Harvestable.h"
#include "Actors/PickupActor.h"


AHarvestable::AHarvestable()
{
	HarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HarvestableMesh->SetupAttachment(RootComponent);
	
	RemainingHarvestableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Remaining Mesh"));
	RemainingHarvestableMesh->SetupAttachment(RootComponent);
	RemainingHarvestableMesh->bHiddenInGame = true;
	RemainingHarvestableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHarvestable::SetHarvestState()
{
	if(!bIsHarvested)
	{
		return;
	}
	HarvestableMesh->DestroyComponent();
	RemainingHarvestableMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RemainingHarvestableMesh->SetHiddenInGame(false);
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
		GetWorld()->SpawnActor<APickupActor>(PickUpActor, SpawnTrans);
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
	FSaveActorData Ret;
	Ret.ActorTransform = this->GetActorTransform();
	Ret.ActorClass = this->GetClass();
	Ret.bWasSpawned = this->bWasSpawned;
	return Ret;
}

void AHarvestable::UpdateFromSave_Implementation()
{
	SetHarvestState();
}
