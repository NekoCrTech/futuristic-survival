#pragma once

#include "CoreMinimal.h"
#include "SalvageItem.generated.h"

USTRUCT(BlueprintType)
struct FSalvageItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Tag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UJunkItemBase> Item;
};

