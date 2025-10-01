// developed by Neko


#include "Interaction/InteractionInterface.h"

FText IInteractionInterface::GetInteractionText_Implementation()
{
	return FText();
}

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.
void IInteractionInterface::Interact_Implementation(class ASurvCharacter* Caller)
{
}

bool IInteractionInterface::IsInteractable_Implementation() const
{
	return true;
}
