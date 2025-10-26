// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurvBlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum EHitDirection : uint8
{
	Left UMETA(Display = "Left"),
	Right UMETA(Display = "Right"),
	Front UMETA(Display = "Front"),
	Back UMETA(Display = "Back")
};

UCLASS()
class FUTURISTICSURVIVAL_API USurvBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Survival|Utilities")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);

	UFUNCTION(BlueprintPure, Category = "Survival|Utilities")
	static FName GetHitDirectionName(const EHitDirection& HitDirection);
};
