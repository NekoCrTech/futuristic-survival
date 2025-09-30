// developed by Neko


#include "Save/SaveActorInterface.h"

// Add default functionality here for any ISaveActorInterface functions that are not pure virtual.
FGuid ISaveActorInterface::GetActorSaveID_Implementation()
{
	FGuid Ret;
	Ret.Invalidate();
	return Ret;
}

FSaveActorData ISaveActorInterface::GetSaveData_Implementation()
{
	return FSaveActorData();
}

FSaveComponentData ISaveActorInterface::GetSaveComponentData_Implementation()
{
	return FSaveComponentData();
}

void ISaveActorInterface::SetSaveComponentData_Implementation(FSaveComponentData Data)
{
}
