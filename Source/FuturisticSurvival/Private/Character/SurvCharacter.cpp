// Developed by Neko


#include "Public/Character/SurvCharacter.h"

#include "Components/StatlineComponent.h"


ASurvCharacter::ASurvCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
}

void ASurvCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASurvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


