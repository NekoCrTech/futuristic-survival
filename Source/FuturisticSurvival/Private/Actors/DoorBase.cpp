// developed by Neko


#include "Actors/DoorBase.h"

ADoorBase::ADoorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

FText ADoorBase::GetInteractionText_Implementation()
{
	return bIsOpen ? FText::FromString("Close") : FText::FromString("Open");
}

void ADoorBase::Interact_Implementation(class ASurvCharacter* Caller)
{
	Interact(Caller);
}

bool ADoorBase::IsInteractable_Implementation() const
{
	return true;
}




