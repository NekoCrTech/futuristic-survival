// developed by Neko


#include "Player/PlayerWidget.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

ESlateVisibility UPlayerWidget::ToggleCharacterWindow()
{
	switch(CharacterWindow->GetVisibility())
	{
		case ESlateVisibility::Visible:
			CharacterWindow->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case ESlateVisibility::Collapsed:
			CharacterWindow->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"UPlayerWidget::ToggleCharacterWindow - CharacterWindow visibility is not Visible or Collapsed");
			break;
	}
	return CharacterWindow->GetVisibility();
}

void UPlayerWidget::SetLeftPanel(USurvUserWidget* WidgetToSet)
{
	SetPanel(WidgetToSet, LeftPanel);
}

void UPlayerWidget::SetRightPanel(USurvUserWidget* WidgetToSet)
{
	SetPanel(WidgetToSet, RightPanel);
}

void UPlayerWidget::SetMiddlePanel(USurvUserWidget* WidgetToSet)
{
	SetPanel(WidgetToSet, MiddlePanel);
}

void UPlayerWidget::SetPanel(USurvUserWidget* WidgetToSet, UOverlay* Panel)
{
	Panel->ClearChildren();
	Panel->AddChild(WidgetToSet);
	if (LeftPanel && Panel->GetChildrenCount() > 0)
	{
		UWidget* FirstChild = Panel->GetChildAt(0);
		if (FirstChild)
		{
			if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(FirstChild->Slot))
			{
				OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}
		}
	}
}


