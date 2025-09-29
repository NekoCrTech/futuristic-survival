// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "SaveActorInterface.h"
#include "GameFramework/SaveGame.h"
#include "SurvSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvSaveGame : public USaveGame
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TMap<FGuid, FSaveActorData> SaveableActorData;
	UPROPERTY()
	FName CurrentlyLoadedLevel = "NONE";

public:

	void SetSaveActorData(TMap<FGuid, FSaveActorData> Data);
	TMap<FGuid, FSaveActorData> GetSaveActorData();
	void SetCurrentLevel(const FName Level);
	FName GetCurrentLevel();
};
