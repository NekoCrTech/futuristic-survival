// developed by Neko


#include "Actors/HarvestablePickup.h"

AHarvestablePickup::AHarvestablePickup()
{
	PermanentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Permanent Mesh"));
	PermanentMesh->SetupAttachment(RootComponent);
	
	HarvestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Harvest Mesh"));
	HarvestMesh->SetupAttachment(RootComponent);
}

void AHarvestablePickup::UpdateHarvestState()
{
	ChangeMeshCompVisibility(HarvestMesh);
	if (!PermanentMesh->GetStaticMesh())
	{
		Destroy();
	}
}

FText AHarvestablePickup::GetInteractionText_Implementation()
{
	return IsInteractable_Implementation() ? InteractionText : FText();
}

void AHarvestablePickup::Interact_Implementation(class ASurvCharacter* Caller)
{
	// class UInventoryComponent* InvComp = Caller->GetInventory();
	// int rem = -1;
	// if( rem = InvComp->AddItem(InventoryItem, ItemCount) == 0)
	// {
			UpdateHarvestState();
			bIsHarvested = true;
	// 	return;
	// }
	// ItemCount = rem;
	// return;
}

bool AHarvestablePickup::IsInteractable_Implementation() const
{
	return !bIsHarvested;
}

FSaveActorData AHarvestablePickup::GetSaveData_Implementation()
{
	return FSaveActorData(GetActorTransform(),bWasSpawned,this->GetClass());
}

void AHarvestablePickup::UpdateFromSave_Implementation()
{
	UpdateHarvestState();
	
}
