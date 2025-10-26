// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UObject* WidgetOwner = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetOwner(UObject* InOwner);
	
};
