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

	UPROPERTY()
	TMap<FGuid, FSaveActorData> SaveableActorData;
	UPROPERTY()
	class USurvSaveGame* SaveGameObject = nullptr;
	UPROPERTY()
	FString SaveGameName = TEXT("DEFAULT");
	UPROPERTY()
	FName CurrentlyLoadedLevel = "NONE";
	UPROPERTY()
	FSaveActorData PlayerData;

	USurvGameInstance();

	void CreateSaveSlot();
	void GatherActorData();
	void GatherPlayerData();
	void LoadGame();
	void SetPlayerData();

public:

	UFUNCTION(BlueprintCallable)
	void AddActorData(const FGuid& ActorID, FSaveActorData ActorData);
	UFUNCTION(BlueprintCallable)
	FSaveActorData GetActorData(const FGuid& ActorID);

	UFUNCTION(BlueprintCallable)
	void DEV_SaveGame();
	UFUNCTION(BlueprintCallable)
	void DEV_LoadGame();
};
