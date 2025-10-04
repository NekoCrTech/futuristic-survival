// developed by Neko


#include "Actors/PickupActor.h"

APickupActor::APickupActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

FText APickupActor::GetInteractionText_Implementation()
{
	return InteractionText;
}

void APickupActor::Interact_Implementation(class ASurvCharacter* Caller)
{
	Execute_Interact(this,Caller);
	// class UInventoryComponent* InvComp = Caller->GetInventory();
	// int rem = -1;
	// if( rem = InvComp->AddItem(InventoryItem, ItemCount) == 0)
	// {
	// 	Interact(Caller)
	// 	return;
	// }
	// ItemCount = rem;
	// return;
}

bool APickupActor::IsInteractable_Implementation() const
{
	return true;
}

