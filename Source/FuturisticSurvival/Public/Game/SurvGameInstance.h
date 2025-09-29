// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Save/SaveActorInterface.h"
#include "SurvGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	TMap<FGuid, FSaveActorData> SaveableActorData;
	UPROPERTY()
	class USurvSaveGame* SaveGameObject = nullptr;
	FString SaveGameName = TEXT("DEFAULT");
	FName CurrentlyLoadedLevel = "NONE";

	USurvGameInstance();

	void CreateSaveSlot();
	void GatherActorData();

public:

	UFUNCTION(BlueprintCallable)
	void AddActorData(const FGuid& ActorID, FSaveActorData ActorData);
	UFUNCTION(BlueprintCallable)
	FSaveActorData GetActorData(const FGuid& ActorID);
};
