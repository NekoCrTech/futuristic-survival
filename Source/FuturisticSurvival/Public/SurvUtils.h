// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemQuality.h"
#include "Enums/RandomizedVector.h"

TArray<FString> ChopString(FString Source, char split = '|');

FLinearColor GetItemQualityColor(const EItemQuality& ItemQuality);

int32 RandomIntFromVector(const ERandomizedVector& DirectionalRandomization, const FVector& Location);
