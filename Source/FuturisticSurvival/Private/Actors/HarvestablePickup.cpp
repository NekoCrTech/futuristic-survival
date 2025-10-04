// developed by Neko


#include "Actors/HarvestablePickup.h"

AHarvestablePickup::AHarvestablePickup()
{
	PermanentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Permanent Mesh"));
	PermanentMesh->SetupAttachment(RootComponent);
	ChangeMeshCompVisibility(PermanentMesh);
	
	HarvestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Harvest Mesh"));
	HarvestMesh->SetupAttachment(RootComponent);
}

FText AHarvestablePickup::GetInteractionText_Implementation()
{
	return IInteractionInterface::GetInteractionText_Implementation();
}

void AHarvestablePickup::Interact_Implementation(class ASurvCharacter* Caller)
{
	Execute_Interact(this,Caller);
	// class UInventoryComponent* InvComp = Caller->GetInventory();
	// int rem = -1;
	// if( rem = InvComp->AddItem(InventoryItem, ItemCount) == 0)
	// {
	ChangeMeshCompVisibility(HarvestMesh);
	if (!PermanentMesh->GetStaticMesh())
	{
		Destroy();
		return;
	}
	ChangeMeshCompVisibility(PermanentMesh, true, ECollisionEnabled::QueryOnly);
	bIsHarvested = true;
	// 	return;
	// }
	// ItemCount = rem;
	// return;
}

bool AHarvestablePickup::IsInteractable_Implementation()
{
	return !bIsHarvested;
}
