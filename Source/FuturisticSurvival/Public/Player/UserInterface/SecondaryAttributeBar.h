// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "SecondaryAttributeBar.generated.h"

class UImage;
class UProgressBar;

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USecondaryAttributeBar : public USurvUserWidget
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UProgressBar* AttributeBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UProgressBar* ReverseAttributeBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UImage* AttributeIcon;
};
