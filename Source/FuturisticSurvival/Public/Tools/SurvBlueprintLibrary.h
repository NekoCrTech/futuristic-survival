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

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor = nullptr;

	UPROPERTY(BlueprintReadWrite)
	float Distance = 0.0f;

	// Default constructor
	FClosestActorWithTagResult(): Actor(nullptr), Distance(0.f)	{}
	
	// Parameterized constructor
	FClosestActorWithTagResult(AActor* InActor, float InDistance): Actor(InActor), Distance(InDistance) {}
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

	UFUNCTION(BlueprintCallable, Category = "Survival|Utilities")
	static FClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag);
};
