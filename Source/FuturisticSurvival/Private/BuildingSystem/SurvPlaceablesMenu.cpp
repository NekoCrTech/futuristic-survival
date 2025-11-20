// developed by Neko


#include "BuildingSystem/SurvPlaceablesMenu.h"
#include "Components/UniformGridPanel.h"
#include "Components/WidgetSwitcher.h" 
#include "BuildingSystem/PlaceableButtonWidget.h"
#include "BuildingSystem/Placeables/SurvPlaceableBase.h"
#include "UserInterface/Primitive/IndexButtonWithText.h"

void USurvPlaceablesMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USurvPlaceablesMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	Buttons.Empty();
	
	Buttons.Add(BuildingButton);
	Buttons.Add(CraftingButton);
	Buttons.Add(FurnitureButton);
	Buttons.Add(MachineryButton);
	Buttons.Add(DefenceButton);
	Buttons.Add(MiscButton);

	int32 Index = 0;
	for (UIndexButtonWithText* Btn : Buttons)
	{
		if (Btn)
		{
			Btn->SetIndex(Index);
			Index++;
		}
	}
	
	// If you also want to bind events for each:
	for (UIndexButtonWithText* Btn : Buttons)
	{
		if (Btn)
		{
			Btn->OnButtonClicked.AddDynamic(this, &USurvPlaceablesMenu::HandleIndexButtonClicked);
		}
	}
	Buttons[0]->SetIsSelected(true);
}

void USurvPlaceablesMenu::HandleIndexButtonClicked(int32 InIndex)
{
	if(SelectedIdx == InIndex) return;
	
	Buttons[SelectedIdx]->SetIsSelected(false);
	SelectedIdx = InIndex;
	Buttons[SelectedIdx]->SetIsSelected(true);
	CategoryWidgetSwitcher->SetActiveWidgetIndex(InIndex);
}

void USurvPlaceablesMenu::UpdatePanels(TArray<TSubclassOf<USurvPlaceableBase>> UnlockedPlaceables)
{
	for (auto PlaceableClass : UnlockedPlaceables)
	{
		UPlaceableButtonWidget* Button = CreateWidget<UPlaceableButtonWidget>(this,PlaceableButtonClass);
		Button->SetPlaceableClass(PlaceableClass);
		
		// Add to the correct panel
		UUniformGridPanel* GridPanel = GetPanelFromCategory(PlaceableClass.GetDefaultObject()->GetCategory());
		int32 GridNewIndex = GridPanel->GetChildrenCount();
		GridPanel->AddChildToUniformGrid(Button,GridNewIndex/ButtonsPerRow,GridNewIndex%ButtonsPerRow);
		
		Button->OnPlaceableButtonClicked.AddDynamic(this, &USurvPlaceablesMenu::HandlePlaceableButtonClicked);
	}
}

UUniformGridPanel* USurvPlaceablesMenu::GetPanelFromCategory(const EPlaceableCategory Category) const
{
	switch (Category) {
	case EPlaceableCategory::Building:
		return BuildingPanel;
	case EPlaceableCategory::Crafting:
		return CraftingPanel;
	case EPlaceableCategory::Furniture:
		return FurniturePanel;
	case EPlaceableCategory::Machinery:
		return MachineryPanel;
	case EPlaceableCategory::Defence:
		return DefencePanel;
	case EPlaceableCategory::Misc:
		return MiscPanel;
	}
	return nullptr;
}

void USurvPlaceablesMenu::HandlePlaceableButtonClicked(const TSubclassOf<USurvPlaceableBase> PlaceableClass)
{
	OnPlaceableSelected.Broadcast(PlaceableClass);
}

