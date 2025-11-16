// developed by Neko

#include "Actors/SurvContainer.h"
#include "GameFramework/HUD.h"
#include "InventorySystem/InventoryComponent.h"
#include "UserInterface/HudInterface.h"

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
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	AHUD* HUD = PC->GetHUD();
	if (!HUD) return;
	
	if (HUD->GetClass()->ImplementsInterface(UHudInterface::StaticClass()))
	{
		IHudInterface::Execute_ToggleCharacterWindow(HUD,true);
	}
	
	InventoryComponent->UpdateInventoryWidget();
}

bool ASurvContainer::IsInteractable_Implementation() const
{
	return true;
}


