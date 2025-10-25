#pragma once

#include "CoreMinimal.h"
#include "InventoryData.generated.h"

class UInventoryWidget;

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData")
	float MaxWeight = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData")
	int32 Capacity = -1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "Survival|InventoryData")
	int32 Columns = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Survival|InventoryData")
	TSubclassOf<UInventoryWidget> InventoryWidget;

	// Default constructor (needed for USTRUCTs)
	FInventoryData() {}

	// Parameterized constructor for easy setup
	FInventoryData(float InMaxWeight, int32 InCapacity, int32 InColumns, TSubclassOf<UInventoryWidget> InWidget)
		: MaxWeight(InMaxWeight)
		, Capacity(InCapacity)
		, Columns(InColumns)
		, InventoryWidget(InWidget)
	{}
};
