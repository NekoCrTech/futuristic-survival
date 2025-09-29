// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveActorInterface.generated.h"


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
	FGuid GetActorID();
	virtual FGuid GetActorID_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	FSaveActorData GetSaveData();
	virtual FSaveActorData GetSaveData_Implementation();
};
