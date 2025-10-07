// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "TimeData.generated.h"

USTRUCT(BlueprintType)
struct FTimeData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int Year = 3000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int Month = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int Day = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int Hour = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int Minute = 0;
	
};
