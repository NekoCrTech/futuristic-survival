// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Placeables/PlaceableCategoryEnum.h"
#include "SurvPlaceablesMenu.generated.h"

class UPlaceableButtonWidget;
class USurvPlaceableBase;
class UWidgetSwitcher;
class UIndexButtonWithText;
class UUniformGridPanel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlaceableSelected, TSubclassOf<USurvPlaceableBase>, PlaceableClass);

UCLASS()
class FUTURISTICSURVIVAL_API USurvPlaceablesMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	
#pragma region Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* BuildingButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* CraftingButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* FurnitureButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* MachineryButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* DefenceButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UIndexButtonWithText* MiscButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UWidgetSwitcher* CategoryWidgetSwitcher;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* BuildingPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* CraftingPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* FurniturePanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* MachineryPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* DefencePanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	UUniformGridPanel* MiscPanel;
	
	
#pragma endregion
	
	UFUNCTION(BlueprintCallable)
	void HandleIndexButtonClicked(int32 InIndex);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePanels(TArray<TSubclassOf<USurvPlaceableBase>> UnlockedPlaceables);
	
	UPROPERTY(BlueprintAssignable)
	FOnPlaceableSelected OnPlaceableSelected;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Settings")
	TSubclassOf<UPlaceableButtonWidget> PlaceableButtonClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Settings")
	int32 ButtonsPerRow = 5;
	
	UPROPERTY()
	TArray<UIndexButtonWithText*> Buttons;
	UPROPERTY()
	int32 SelectedIdx;
	
	UUniformGridPanel* GetPanelFromCategory(EPlaceableCategory Category) const;
	
	UFUNCTION()
	void HandlePlaceableButtonClicked(TSubclassOf<USurvPlaceableBase> PlaceableClass);
	
	
};
