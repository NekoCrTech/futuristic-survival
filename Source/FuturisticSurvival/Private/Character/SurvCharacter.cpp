// Developed by Neko


#include "Public/Character/SurvCharacter.h"

#include "Components/StatlineComponent.h"


ASurvCharacter::ASurvCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
	Statline->SetMovementCompReference(GetCharacterMovement());
}

void ASurvCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASurvCharacter::CanJump() const
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


void ASurvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


