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
	FVector Location = FVector(0);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AttachmentPointData")
	TArray<EBuildingPartType> PartsToSnap;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AttachmentPointData")
	bool bRotate = false;
};
