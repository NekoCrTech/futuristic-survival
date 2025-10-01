// developed by Neko


#include "Core/SurvActor.h"


ASurvActor::ASurvActor()
{
 	
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
	FSaveActorData Ret;
	Ret.ActorTransform = this->GetActorTransform();
	Ret.ActorClass = this->GetClass();
	Ret.bWasSpawned = this->bWasSpawned;
	return Ret;
}

void ASurvActor::UpdateFromSave_Implementation()
{
	Execute_UpdateFromSave(this);
}

