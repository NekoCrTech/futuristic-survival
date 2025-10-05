// Developed by Neko


#include "Public/Character/SurvCharacter.h"
#include "Structs/SaveActorData.h"
#include "Components/StatlineComponent.h"
#include "InventorySystem/InventoryComponent.h"


ASurvCharacter::ASurvCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
	Statline->SetMovementCompReference(GetCharacterMovement());

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

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
	return FSaveActorData(this->GetTransform(), this->bWasSpawned, this->GetClass());
}

void ASurvCharacter::SetActorGUID_Implementation(const FGuid& NewGiud)
{
	if (SaveActorID.IsValid())
	{
		SaveActorID.Invalidate();
	}

	SaveActorID = NewGiud;
}

void ASurvCharacter::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}


