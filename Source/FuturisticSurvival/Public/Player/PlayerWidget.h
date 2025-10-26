// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvUserWidget.h"
#include "PlayerWidget.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UPlayerWidget : public USurvUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	ESlateVisibility ToggleCharacterWindow();

	UFUNCTION(BlueprintCallable)
	void SetLeftPanel(USurvUserWidget* WidgetToSet);
	UFUNCTION(BlueprintCallable)
	void SetRightPanel(USurvUserWidget* WidgetToSet);
	UFUNCTION(BlueprintCallable)
	void SetMiddlePanel(USurvUserWidget* WidgetToSet);

private:
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget, AllowPrivateAccess = "true"), Category = "Survival|Components")
	UOverlay* CharacterWindow;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget, AllowPrivateAccess = "true"), Category = "Survival|Components")
	UOverlay* LeftPanel;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget, AllowPrivateAccess = "true"), Category = "Survival|Components")
	UOverlay* MiddlePanel;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget, AllowPrivateAccess = "true"), Category = "Survival|Components")
	UOverlay* RightPanel;

	void SetPanel(USurvUserWidget* WidgetToSet, UOverlay* Panel);
	
};
