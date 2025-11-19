// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HudInterface.generated.h"

class USurvPlaceablesMenu;
class UInventoryWidget;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHudInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FUTURISTICSURVIVAL_API IHudInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleCharacterWindow(bool bUseOtherInventory = false);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UInventoryWidget* CreateInventoryWidget(AActor* InOwner, const FInventoryData& InventoryData);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	USurvPlaceablesMenu* GetPlaceablesMenu();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TogglePlacementWindow();
};
