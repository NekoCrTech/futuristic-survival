// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "BuildingPartType.generated.h"

UENUM(BlueprintType)
enum class EBuildingPartType : uint8
{
	Other UMETA(DisplayName = "Other"),
	Floor UMETA(DisplayName = "Floor"),
	Wall UMETA(DisplayName = "Wall"),
	Ceiling UMETA(DisplayName = "Ceiling"),
};
