// developed by Neko


#include "Actors/SurvContainer.h"

#include "InventorySystem/InventoryComponent.h"

ASurvContainer::ASurvContainer()
{
	PrimaryActorTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

FText ASurvContainer::GetInteractionText_Implementation()
{
	return FText::FromString("Open Container");
}

void ASurvContainer::Interact_Implementation(class ASurvCharacter* Caller)
{
	InventoryComponent->CreateInventoryWidget();
	//ASurvPlayerCharacter* PlayerCharacter = Cast<ASurvPlayerCharacter>(Caller);
	//if(!PlayerCharacter) return;
	//PlayerCharacter->TogglePlayerWindow(true);
	InventoryComponent->UpdateInventoryWidget();
}

bool ASurvContainer::IsInteractable_Implementation() const
{
	return true;
}


