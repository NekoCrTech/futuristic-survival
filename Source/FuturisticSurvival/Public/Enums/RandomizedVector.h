// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "RandomizedVector.generated.h"


UENUM(BlueprintType)
enum class ERandomizedVector : uint8
{
	X,
	Y,
	Z,
	XY,
	XZ,
	YZ,
	XYZ
};
