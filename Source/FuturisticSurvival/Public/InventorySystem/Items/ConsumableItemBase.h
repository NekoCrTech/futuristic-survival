// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemBase.h"
#include "Enums/StatEnum.h"
#include "ConsumableItemBase.generated.h"


UCLASS(Blueprintable)
class FUTURISTICSURVIVAL_API UConsumableItemBase : public UItemBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EStat, float> StatAdjustments;

public:

	void OnUse(class ASurvCharacter* Caller) override;
	
};
