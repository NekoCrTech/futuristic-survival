// developed by Neko


#include "Save/SurvSaveGame.h"
#include "Structs/SaveActorData.h"
#include "Structs/SaveComponentData.h"



void USurvSaveGame::SetSaveActorData(TMap<FGuid, FSaveActorData> Data)
{
	SaveableActorData = Data;
}

TMap<FGuid, FSaveActorData> USurvSaveGame::GetSaveActorData()
{
	return SaveableActorData;
}

void USurvSaveGame::SetCurrentLevel(const FName Level)
{
	CurrentlyLoadedLevel = Level;
}

FName USurvSaveGame::GetCurrentLevel()
{
	return CurrentlyLoadedLevel;
}

void USurvSaveGame::SetPlayerData(FSaveActorData Data)
{
	PlayerData = Data;
}

FSaveActorData USurvSaveGame::GetPlayerData()
{
	return PlayerData;
}
