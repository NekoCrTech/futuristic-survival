// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "PlayerHud.generated.h"

class UInventoryWidget;
class UOverlay;
class UBarXP;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UPlayerHud : public USurvUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UBarXP* BarXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UInventoryWidget* PlayerInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UOverlay* CharacterMenuOverlay;
	
	UFUNCTION(BlueprintCallable, Category="Survival")
	ESlateVisibility ToggleCharacterWindow(bool bUseOtherInventory = false);
};
