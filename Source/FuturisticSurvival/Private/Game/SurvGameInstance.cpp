// developed by Neko


#include "Game/SurvGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Save/SurvSaveGame.h"
#include "EngineUtils.h"
#include "Logger.h"
#include "Core/SurvActor.h"
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>
#include "GameFramework/Character.h"
#include "SaveGameSystem.h"
#include "Character/SurvCharacter.h"


USurvGameInstance::USurvGameInstance()
{
	SaveNames = GetAllSaveGameNames();
}

void USurvGameInstance::CreateSaveSlot()
{
	SaveGameObject = Cast<USurvSaveGame>(UGameplayStatics::CreateSaveGameObject(USurvSaveGame::StaticClass()));
}

void USurvGameInstance::GatherActorData()
{
	for (FActorIterator ActorItr(GetWorld()); ActorItr; ++ActorItr )
	{
		AActor* Actor = *ActorItr;
		if (!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		FGuid SAI = Inter->GetActorSaveID_Implementation();
		if (!SAI.IsValid())
		{
			continue;
		}
		FSaveActorData SAD = Inter->GetSaveData_Implementation();
		FMemoryWriter NemWriter(SAD.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(NemWriter,true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);

		for ( auto ActorComp : Actor->GetComponents())
		{
			if (!ActorComp->Implements<USaveActorInterface>())
			{
				continue;
			}
			ISaveActorInterface* InterComp = Cast<ISaveActorInterface>(ActorComp);
			if (InterComp == nullptr)
			{
				continue;
			}
			FSaveComponentData SCD = InterComp->GetSaveComponentData_Implementation();
			FMemoryWriter CompNemWriter(SCD.ByteData);
			FObjectAndNameAsStringProxyArchive CAr(CompNemWriter, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			SCD.ComponentClass = ActorComp->GetClass();

			SAD.ComponentData.Add(SCD);
		}

		SaveableActorData.Add(SAI, SAD);
	}

	GatherPlayerData();
}

void USurvGameInstance::GatherPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ISaveActorInterface* Inter = Cast<ISaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr)
	{
		// TODO: log error
		return;
	}
	FSaveActorData SAD = Inter->GetSaveData_Implementation();
	FMemoryWriter NemWriter(SAD.ByteData);
	FObjectAndNameAsStringProxyArchive Ar(NemWriter,true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);

	for ( auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!ActorComp->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* InterComp = Cast<ISaveActorInterface>(ActorComp);
		if (InterComp == nullptr)
		{
			continue;
		}
		FSaveComponentData SCD = InterComp->GetSaveComponentData_Implementation();
		FMemoryWriter CompNemWriter(SCD.ByteData);
		FObjectAndNameAsStringProxyArchive CAr(CompNemWriter, true);
		CAr.ArIsSaveGame = true;
		ActorComp->Serialize(CAr);
		SCD.ComponentClass = ActorComp->GetClass();

		SAD.ComponentData.Add(SCD);
	}
	PlayerData = SAD;
}

void USurvGameInstance::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameName, 0))
	{
		Logger::GetInstance()->AddMessage("Load game called with invalid save name", EErrorLevel::EL_WARNING);
		return;
	}
	
	SaveableActorData.Empty();
	SaveGameObject = Cast<USurvSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameName, 0));
	SaveableActorData = SaveGameObject->GetSaveActorData();
	PlayerData = SaveGameObject->GetPlayerData();
	CurrentlyLoadedLevel = SaveGameObject->GetCurrentLevel();
	LoadGameLevel(CurrentlyLoadedLevel);

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if(!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		if (Inter->Execute_GetSaveData(Actor).bWasSpawned)
		{
			Actor->Destroy();
		}
	}

	for (TTuple<FGuid,FSaveActorData> SAD : SaveableActorData)
	{
		if (SAD.Value.bWasSpawned)
		{
			UClass* ToSpawnClass = SAD.Value.ActorClass;
			if (ToSpawnClass->IsChildOf(ASurvCharacter::StaticClass()))
			{
				ASurvCharacter* CSpawned = GetWorld()->SpawnActor<ASurvCharacter>(ToSpawnClass, SAD.Value.ActorTransform);
				ISaveActorInterface* Inter = Cast<ISaveActorInterface>(CSpawned);
				if (Inter == nullptr)
				{
					CSpawned->Destroy();
					continue;
				}
				Inter->Execute_SetActorGUID(CSpawned, SAD.Key);
				CSpawned->SetWasSpawned(true);
				continue;
			}
			ASurvActor* Spawned = GetWorld()->SpawnActor<ASurvActor>(ToSpawnClass, SAD.Value.ActorTransform);
			ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Spawned);
			if (Inter == nullptr)
			{
				Spawned->Destroy();
				continue;
			}
			Inter->Execute_SetActorGUID(Spawned, SAD.Key);
			Spawned->SetWasSpawned(true);
		}
	}

	for (FActorIterator ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		if(!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		FGuid SAI = Inter->GetActorSaveID_Implementation();
		if (!SaveableActorData.Find(SAI))
		{
			continue;
		}
		FSaveActorData SAD = SaveableActorData[SAI];
		Actor->SetActorTransform(SAD.ActorTransform);

		FMemoryReader NemReader(SAD.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(NemReader,true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);
		Inter->Execute_UpdateFromSave(Actor);
		Inter->Execute_SetActorRawSaveData(Actor, SAD.RawData);
		for (auto ActorComp : Actor->GetComponents())
		{
			if (!ActorComp->Implements<USaveActorInterface>())
			{
				continue;
			}
			ISaveActorInterface* InterComp = Cast<ISaveActorInterface>(ActorComp);
			if (InterComp == nullptr)
			{
				continue;
			}
			for (auto SCD : SAD.ComponentData)
			{
				/***************************************************************************
				 *This is not safe is an actor has 2 of the same components, that are saved*
				 *as the 1st component returned by Actor->GetComponents() will get all data*
				 *
				 *		One Possible option is a GUID on the Component
				 **************************************************************************/
				
				if (SCD.ComponentClass != ActorComp->GetClass())
				{
					continue;
				}

				FMemoryReader CompNemReader(SCD.ByteData);
				FObjectAndNameAsStringProxyArchive CAr(CompNemReader, true);
				CAr.ArIsSaveGame = true;
				ActorComp->Serialize(CAr);
				if (SCD.RawData.IsEmpty())
				{
					break;
				}
				InterComp->SetSaveComponentData_Implementation(SCD);
				break;
			}
		}
	}

	SetPlayerData();
}

void USurvGameInstance::SetPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ISaveActorInterface* Inter = Cast<ISaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr)
	{
		// log error
		return;
	}

	PlayerCharacter->SetActorTransform(PlayerData.ActorTransform);
	FMemoryReader NemReader(PlayerData.ByteData);
	FObjectAndNameAsStringProxyArchive Ar(NemReader,true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);

	for (auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!ActorComp->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* InterComp = Cast<ISaveActorInterface>(ActorComp);
		if (InterComp == nullptr)
		{
			continue;
		}
		for (auto SCD : PlayerData.ComponentData)
		{
			/***************************************************************************
			 *This is not safe is an actor has 2 of the same components, that are saved*
			 *as the 1st component returned by Actor->GetComponents() will get all data*
			 *
			 *		One Possible option is a GUID on the Component
			 **************************************************************************/
				
			if (SCD.ComponentClass != ActorComp->GetClass())
			{
				continue;
			}

			FMemoryReader CompNemReader(SCD.ByteData);
			FObjectAndNameAsStringProxyArchive CAr(CompNemReader, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			if (SCD.RawData.IsEmpty())
			{
				break;
			}
			InterComp->SetSaveComponentData_Implementation(SCD);
			break;
		}
	}
}

TArray<FString> USurvGameInstance::GetAllSaveGameNames()
{
	TArray<FString> Ret;
	FString SavePath = FPaths::ProjectSavedDir();
	SavePath += "SaveGames/*";
	//Logger::GetInstance()->AddMessage("USurvGameInstance::GetAllSaveGameNames found the following save path", EL_DEBUG);
	WIN32_FIND_DATA FindData;
	HANDLE hFindData = ::FindFirstFile(*SavePath, &FindData);
	if (hFindData == INVALID_HANDLE_VALUE)
	{
		return Ret;
	}

	while (::FindNextFile(hFindData, &FindData))
	{
		if(FindData.cFileName[0] == '\0' ||
			FindData.cFileName[0] == '.' && FindData.cFileName[1] == '\0' ||
			FindData.cFileName[0] == '.' && FindData.cFileName[1] == '\0' && FindData.cFileName[2] == '\0')
		{
			continue;
		}
		FString FileName(FindData.cFileName);
		if (FileName.EndsWith(".sav"))
		{
			Ret.Add(FileName.Mid(0,FileName.Len() - 4));
		}
		
	}
	::FindClose(hFindData);	
	return Ret;
}

void USurvGameInstance::AddActorData(const FGuid& ActorID, FSaveActorData ActorData)
{
	SaveableActorData.Add(ActorID, ActorData);
}

FSaveActorData USurvGameInstance::GetActorData(const FGuid& ActorID)
{
	return SaveableActorData[ActorID];
}

void USurvGameInstance::DEV_SaveGame()
{
	if (SaveGameObject == nullptr)
	{
		CreateSaveSlot();
	}
	GatherActorData();
	SaveGameObject->SetSaveActorData(SaveableActorData);
	SaveGameObject->SetPlayerData(PlayerData);
	SaveGameObject->SetCurrentLevel(CurrentlyLoadedLevel);
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameName, 0);
	SaveNames = GetAllSaveGameNames();
}

void USurvGameInstance::DEV_LoadGame()
{
	LoadGame();
}


void USurvGameInstance::LoadGameLevel(const FName& LevelToLoad)
{
	LoadGameLevelBP(LevelToLoad);
}

TArray<FString> USurvGameInstance::GetSaveGameNames() const
{
	return SaveNames;
}

void USurvGameInstance::SetSaveGameName(const FString& SaveName)
{
	SaveGameName = SaveName;
}

void USurvGameInstance::SetCurrentLevel(const FName& Level)
{
	CurrentlyLoadedLevel = Level;
}

void USurvGameInstance::LoadGameLevelBP_Implementation(const FName& LevelToLoad)
{
}
