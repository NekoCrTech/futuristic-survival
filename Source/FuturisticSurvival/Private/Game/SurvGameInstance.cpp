// developed by Neko


#include "Game/SurvGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Save/SurvSaveGame.h"
#include "EngineUtils.h"
#include "Logger.h"
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>

#include "GameFramework/Character.h"


USurvGameInstance::USurvGameInstance()
{
	
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
		// log error
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
		Logger::GetInstance()->AddMessage("Load game called with invalid save name", ERRORLEVEL::EL_WARNING);
		//TODO: Add logging and error message about missing save game
		return;
	}

	SaveableActorData.Empty();
	SaveGameObject = Cast<USurvSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameName, 0));
	SaveableActorData = SaveGameObject->GetSaveActorData();
	PlayerData = SaveGameObject->GetPlayerData();

	for (TTuple<FGuid,FSaveActorData> SAD : SaveableActorData)
	{
		if (SAD.Value.bWasSpawned)
		{
			AActor* SpawnedActor = GetWorld()->SpawnActor(SAD.Value.ActorClass->StaticClass(), &SAD.Value.ActorTransform);
			ISaveActorInterface* Inter = Cast<ISaveActorInterface>(SpawnedActor);
			if (Inter == nullptr)
			{
				continue;
			}
			Inter->SetActorGUID_Implementation(SAD.Key);
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
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameName, 0);
}

void USurvGameInstance::DEV_LoadGame()
{
	LoadGame();
}
