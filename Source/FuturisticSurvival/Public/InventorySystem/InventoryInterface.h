// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/InventorySlotData.h"
#include "InventoryInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class FUTURISTICSURVIVAL_API IInventoryInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Inventory")
	TMap<FIntPoint, FInventorySlotData> GetInventoryContents() const;


};
