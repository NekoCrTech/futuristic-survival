// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Logger.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurvUtilsFunctions.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvUtilsFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Logging")
	static void AddLogMessage(const FString& Caller, const FString& Message, EErrorLevel Level);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Math")
	static float ConvertFahrenheitToCelsius(const float& Temperature);

private:
	static FColor GetColorByErrorLevel(EErrorLevel Level);
	
};
