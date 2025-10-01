// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveActorInterface.generated.h"

USTRUCT(BlueprintType)
struct FSaveComponentData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UClass* ComponentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> RawData;
};

USTRUCT(BlueprintType)
struct FSaveActorData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FTransform ActorTransform;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<FSaveComponentData> ComponentData;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bWasSpawned = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UClass* ActorClass;	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveActorInterface : public UInterface
{
	GENERATED_BODY()
};


class FUTURISTICSURVIVAL_API ISaveActorInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	FGuid GetActorSaveID();
	virtual FGuid GetActorSaveID_Implementation();
	
	UFUNCTION(BlueprintNativeEvent)
	void SetActorGUID(const FGuid& NewGiud);
	virtual void SetActorGUID_Implementation(const FGuid& NewGiud);

	UFUNCTION(BlueprintNativeEvent)
	FSaveActorData GetSaveData();
	virtual FSaveActorData GetSaveData_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	FSaveComponentData GetSaveComponentData();
	virtual FSaveComponentData GetSaveComponentData_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetSaveComponentData(FSaveComponentData Data);
	virtual void SetSaveComponentData_Implementation(FSaveComponentData Data);
};
