// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/BuildingPartType.h"
#include "AttachmentPointData.generated.h"




USTRUCT(BlueprintType)
struct FAttachmentPointData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AttachmentPointData")
	FVector Position = FVector(0);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AttachmentPointData")
	TArray<EBuildingPartType> PartsToSnap;
};
