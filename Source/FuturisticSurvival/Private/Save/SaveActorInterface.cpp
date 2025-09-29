// developed by Neko


#include "Save/SaveActorInterface.h"

// Add default functionality here for any ISaveActorInterface functions that are not pure virtual.
FGuid ISaveActorInterface::GetActorID_Implementation()
{
	FGuid Ret;
	Ret.Invalidate();
	return Ret;
}

FSaveActorData ISaveActorInterface::GetSaveData_Implementation()
{
	FSaveActorData Ret = FSaveActorData();
	return Ret;
}
