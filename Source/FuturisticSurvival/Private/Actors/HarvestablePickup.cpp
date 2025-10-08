// developed by Neko


#include "Actors/HarvestablePickup.h"
#include "Structs/SaveActorData.h"
#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/Items/ItemBase.h"
#include "Character/SurvCharacter.h"


AHarvestablePickup::AHarvestablePickup()
{
	PermanentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Permanent Mesh"));
	PermanentMesh->SetupAttachment(RootComponent);
	
	HarvestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Harvest Mesh"));
	HarvestMesh->SetupAttachment(RootComponent);
}

void AHarvestablePickup::UpdateHarvestState()
{
	if (!bIsHarvested)
	{
		ChangeMeshCompVisibility(HarvestMesh, true, ECollisionEnabled::QueryOnly);
		return;
	}
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
		bIsHarvested = true;
		UpdateHarvestState();
	}
	ItemCount = Remain;
	return;
	// class UInventoryComponent* InvComp = Caller->GetInventory();
	// int rem = -1;
	// if( rem = InvComp->AddItem(InventoryItem, ItemCount) == 0)
	// {
	//	UpdateHarvestState();
	//	bIsHarvested = true;	
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

bool AHarvestablePickup::GetMustShowWidget() const
{
	return (IsInteractable_Implementation() && !bIsHarvested);
}
