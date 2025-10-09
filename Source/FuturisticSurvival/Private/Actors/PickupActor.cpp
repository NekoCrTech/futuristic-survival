// developed by Neko


#include "Actors/PickupActor.h"
#include "Character/SurvCharacter.h"
#include "InventorySystem/Items/ItemBase.h"
#include "InventorySystem/InventoryComponent.h"

APickupActor::APickupActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent=Mesh;

	Root->DestroyComponent();
}

FText APickupActor::GetInteractionText_Implementation()
{
	return InteractionText;
}

void APickupActor::Interact_Implementation(class ASurvCharacter* Caller)
{
	if (!IsValid(InventoryItem))
	{
		//TODO: Add Logging system
		return;
	}
	if(!IsInteractable_Implementation())
	{
		return;
	}
	UInventoryComponent* Inventory = Caller->GetInventory();
	int Remain = ItemCount;
	
	while (Remain > 0 && Inventory->AddItemToTop(InventoryItem))
	{
		Remain--;
	}
	if (Remain == 0)
	{
		this->Destroy();
		//this->SetAutoDestroyWhenFinished(true);
	}
	ItemCount = Remain;
	return;
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
	return IsValid(InventoryItem);
}

