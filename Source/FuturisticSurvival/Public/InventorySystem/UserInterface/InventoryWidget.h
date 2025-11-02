// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "Structs/InventoryData.h"
#include "Structs/InventorySlotData.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UInventoryWidget : public USurvUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void UpdateContents();

	UFUNCTION(BlueprintNativeEvent)
	void OnInventoryUpdate(const TMap<FIntPoint, FInventorySlotData>& Contents);
	void SetInventoryData(const FInventoryData& InventoryDataToSet);
	
	bool GetIsOnScreen() const {return bIsOnScreen;}
	void SetIsOnScreen(const bool& bValue) {bIsOnScreen = bValue;}
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess = "true"), category = "Survival|Components")
	UUniformGridPanel* InventoryGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Survival|Data")
	FInventoryData InventoryData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Survival|Data")
	bool bIsOnScreen = false;
};
