// developed by Neko


#include "InventorySystem/Items/ItemBase.h"


int32 UItemBase::AddToCurrentStack(const int& Amount)
{
	int32 remains = 0;
	if (CurrentStackSize == MaxStackSize)
	{
		return Amount;
	}

	remains = FMath::Clamp(Amount - (MaxStackSize-CurrentStackSize), 0, Amount);
	CurrentStackSize += Amount - remains;
	return remains;
}

int UItemBase::RemoveFromStack(const int& Amount)
{
	if (CurrentStackSize < Amount)
	{
		int removed = CurrentStackSize;
		CurrentStackSize = 0;
		return removed;
	}
	CurrentStackSize -= Amount;
	return 0;
}
