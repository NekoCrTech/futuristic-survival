// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/UserInterface/SurvInventorySlot.h"
#include "EmptyInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UEmptyInventorySlot : public USurvInventorySlot
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetLocation(const FIntPoint& Location) { SlotLocation = Location; }
	
};
