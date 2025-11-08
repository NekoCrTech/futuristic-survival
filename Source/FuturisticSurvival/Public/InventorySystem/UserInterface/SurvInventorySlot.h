// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "SurvInventorySlot.generated.h"

class UTextBlock;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvInventorySlot : public USurvUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), category = "Survival|Components")
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, category = "Survival|Inventory")
	FIntPoint SlotLocation;
};
