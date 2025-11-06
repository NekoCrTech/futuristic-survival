// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "BarXP.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UBarXP : public USurvUserWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	class UProgressBar* ProgressBarXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	class UTextBlock* TextXP;

	UFUNCTION(BlueprintCallable)
	void SetXPBar(int32 CurrentXP, int32 XpToLevelUp);
};
