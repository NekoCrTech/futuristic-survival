#pragma once

#include "CoreMinimal.h"
#include "StatEnum.generated.h"

UENUM(BlueprintType)
enum class EStat : uint8 
{
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Energy UMETA(DisplayName = "Energy"),
	Thirst UMETA(DisplayName = "Thirst"),
	Hunger UMETA(DisplayName = "Hunger")
};
