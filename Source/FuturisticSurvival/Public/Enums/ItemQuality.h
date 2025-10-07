#pragma once

#include "CoreMinimal.h"
#include "ItemQuality.generated.h"

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Shoddy      UMETA(DisplayName = "Shoddy"),
	Common      UMETA(DisplayName = "Common"),
	Quality     UMETA(DisplayName = "Quality"),
	Masterwork  UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};