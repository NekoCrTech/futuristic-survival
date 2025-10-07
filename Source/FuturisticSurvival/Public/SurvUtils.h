// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemQuality.h"

TArray<FString> ChopString(FString Source, char split = '|');

FLinearColor GetItemQualityColor(const EItemQuality& ItemQuality);
