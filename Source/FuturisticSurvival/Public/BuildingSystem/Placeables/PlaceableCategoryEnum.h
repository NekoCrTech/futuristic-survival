#pragma once

#include "CoreMinimal.h"
#include "PlaceableCategoryEnum.generated.h"

UENUM(BlueprintType)
enum class EPlaceableCategory : uint8
{
	Building UMETA(DisplayName = "Building"),
	Crafting UMETA(DisplayName = "Crafting"),
	Furniture UMETA(DisplayName = "Furniture"),
	Machinery UMETA(DisplayName = "Machinery"),
	Defence UMETA(DisplayName = "Defence"),
	Misc UMETA(DisplayName = "Misc")
};
