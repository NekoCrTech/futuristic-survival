// developed by Neko


#include "BuildingSystem/PlaceableButtonWidget.h"

#include "BuildingSystem/Placeables/SurvPlaceableBase.h"
#include "Components/Image.h"
#include "Components/Button.h"


void UPlaceableButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnClicked.AddDynamic(this, &UPlaceableButtonWidget::HandleButtonClicked);
}

void UPlaceableButtonWidget::SetPlaceableClass(TSubclassOf<USurvPlaceableBase> InPlaceableClass)
{
	PlaceableClass = InPlaceableClass;
	PlaceableIcon->SetBrushFromTexture(PlaceableClass.GetDefaultObject()->GetIcon());
}

void UPlaceableButtonWidget::HandleButtonClicked()
{
	OnPlaceableButtonClicked.Broadcast(PlaceableClass);
}
