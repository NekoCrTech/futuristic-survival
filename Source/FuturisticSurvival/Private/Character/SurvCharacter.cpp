// developed by Neko


#include "Public/Character/SurvCharacter.h"

// Sets default values
ASurvCharacter::ASurvCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASurvCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASurvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

