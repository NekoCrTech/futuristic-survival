// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/SaveActorData.h"
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
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "level", meta = (AllowPrivateAccess = "true"))
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


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadGameLevelBP(const FName& LevelToLoad);
	UFUNCTION(BlueprintCallable)
	void LoadGameLevel(const FName& LevelToLoad);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool NoLevelLoaded() const {return CurrentlyLoadedLevel == FName("NONE");}
};
