// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "PlayerHud.generated.h"

class USurvPlaceablesMenu;
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
	
	void SetOtherInventory(UInventoryWidget* OtherInventoryWidget);
	void CloseOtherInventory();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UBarXP* BarXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UInventoryWidget* PlayerInventoryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	USurvPlaceablesMenu* PlaceablesMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UOverlay* CharacterMenuOverlay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), category = "Components")
	UOverlay* OtherInventoryOverlay;
	
	UFUNCTION(BlueprintCallable, Category="Survival")
	ESlateVisibility ToggleCharacterWindow();
};
