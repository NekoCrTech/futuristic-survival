// developed by Neko


#include "InventorySystem/Items/ConsumableItemBase.h"
#include "Character/SurvCharacter.h"
#include "Components/StatlineComponent.h"

void UConsumableItemBase::OnUse(ASurvCharacter* Caller)
{
	UStatlineComponent* Statline = Caller->GetStatline();
	for (TPair<EStat, float>& affect : StatAdjustments)
	{
		Statline->AdjustStat(affect.Key, affect.Value);
	}
}
