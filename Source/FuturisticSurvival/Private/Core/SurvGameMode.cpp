// developed by Neko


#include "Public/Core/SurvGameMode.h"

#include "Actors/Chronomanager.h"
#include "Kismet/GameplayStatics.h"

void ASurvGameMode::InitializeChronomanager()
{
	AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AChronomanager::StaticClass());
	Chronomanager = Cast<AChronomanager>(Actor);
	if (!Chronomanager)
	{
		Logger::GetInstance()->AddMessage("ASurvGameMode::InitializeChronoManager - Chonomanager not found on world", EErrorLevel::EL_CRITICAL);
		GEngine->AddOnScreenDebugMessage(100,5,FColor::Red,TEXT("ASurvGameMode::InitializeChronoManager - Chronomanager not found on world "));
	}
}
