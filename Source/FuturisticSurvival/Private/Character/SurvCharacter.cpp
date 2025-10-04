// Developed by Neko


#include "Public/Character/SurvCharacter.h"

#include "Components/StatlineComponent.h"


ASurvCharacter::ASurvCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
	Statline->SetMovementCompReference(GetCharacterMovement());

	SaveActorID = FGuid::NewGuid();
}

void ASurvCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!SaveActorID.IsValid())
	{
		SaveActorID = FGuid::NewGuid();
	}
	
}

bool ASurvCharacter::CanCharJump() const
{
	return Statline->CanJump();
}

void ASurvCharacter::HasJumped()
{
	Statline->HasJumped();
	ACharacter::Jump();
}

bool ASurvCharacter::CanSprint() const
{
	return Statline->CanSprint();
}

void ASurvCharacter::SetSprinting(const bool& IsSprinting)
{
	Statline->SetSprinting(IsSprinting);
}

void ASurvCharacter::SetSneaking(const bool& IsSneaking)
{
	Statline->SetSneaking(IsSneaking);
}


void ASurvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FGuid ASurvCharacter::GetActorSaveID_Implementation()
{
	
	return SaveActorID;
}

FSaveActorData ASurvCharacter::GetSaveData_Implementation()
{
	FSaveActorData Ret;

	Ret.ActorClass = this->GetClass();
	Ret.ActorTransform = this->GetTransform();
	Ret.bWasSpawned = this->bWasSpawned;
	
	return Ret;
}

void ASurvCharacter::SetActorGUID_Implementation(const FGuid& NewGiud)
{
	if (SaveActorID.IsValid())
	{
		SaveActorID.Invalidate();
	}

	SaveActorID = NewGiud;
}

void ASurvCharacter::SetWasSpawned(bool IsSpawned)
{
	bWasSpawned = IsSpawned;
}


