#pragma once

#include "CoreMinimal.h"
#include "Structs/SaveComponentData.h"
#include "SaveActorData.generated.h"


USTRUCT(BlueprintType)
struct FSaveActorData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	FTransform ActorTransform;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	TArray<FSaveComponentData> ComponentData;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	bool bWasSpawned = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	UClass* ActorClass = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	TArray<FString> RawData;


	FSaveActorData() = default;

	FSaveActorData(const FTransform& InActorTransform, const bool& InWasSpawned,UClass* InActorClass)
	{
		ActorTransform = InActorTransform;
		bWasSpawned = InWasSpawned;
		ActorClass = InActorClass;
	};

	FSaveActorData(const FTransform& InActorTransform, const bool& InWasSpawned,UClass* InActorClass, const TArray<FString>& InRawData)
	{
		ActorTransform = InActorTransform;
		bWasSpawned = InWasSpawned;
		ActorClass = InActorClass;
		RawData = InRawData;
		
	};
};