// developed by Neko


#include "Actors/PickupActor.h"
#include "Character/SurvCharacter.h"
#include "InventorySystem/Items/ItemBase.h"
#include "InventorySystem/InventoryComponent.h"

APickupActor::APickupActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent=Mesh;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	//Root->DestroyComponent();
}

void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(PhysicsTimer, this, &APickupActor::StopPhysics,3.f,false);
}

FText APickupActor::GetInteractionText_Implementation()
{
	return InteractionText;
}

void APickupActor::Interact_Implementation(class ASurvCharacter* Caller)
{
	if (!Caller || !IsInteractable_Implementation()) return;

	if (UInventoryComponent* Inventory = Caller->GetInventory())
	{
		// Add the item type to the inventory — it handles stacking internally
		if (Inventory->AddItemToInventory(InventoryItem))
		{
			Destroy();
		}
	}
}

bool APickupActor::IsInteractable_Implementation() const
{
	return IsValid(InventoryItem);
}

void APickupActor::SetPickupMesh(UStaticMesh* PickUpMesh)
{
	Mesh->SetStaticMesh(PickUpMesh);
}

void APickupActor::SetInventoryItem(TSubclassOf<UItemBase> Item)
{
	InventoryItem = Item;
	InteractionText = InventoryItem.GetDefaultObject()->GetPickupText();
}

void APickupActor::StopPhysics()
{
	Mesh->SetSimulatePhysics(false);
	GetWorld()->GetTimerManager().ClearTimer(PhysicsTimer);
}

