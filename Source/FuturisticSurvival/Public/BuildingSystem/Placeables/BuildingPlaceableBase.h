// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "SurvPlaceableBase.h"
#include "Enums/BuildingPartType.h"
#include "Structs/AttachmentPointData.h"
#include "BuildingPlaceableBase.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UBuildingPlaceableBase : public USurvPlaceableBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	TArray<FAttachmentPointData> AttachmentPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	EBuildingPartType Type;
	
public:
	TSubclassOf<APlaceableActor> GetBuildable() {return Buildable;}
	TArray<FAttachmentPointData> GetAttachments() const {return AttachmentPoints;}
	EBuildingPartType GetType() const {return Type;}
};
