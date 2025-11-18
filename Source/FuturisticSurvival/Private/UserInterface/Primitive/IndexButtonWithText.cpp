// developed by Neko


#include "UserInterface/Primitive/IndexButtonWithText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"



void UIndexButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!ButtonLabel.IsEmpty())
	{
		ButtonTextBlock->SetText(ButtonLabel);
	}
}

void UIndexButtonWithText::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnClicked.AddDynamic(this, &ThisClass::HandleButtonClicked);
}



void UIndexButtonWithText::SetIsSelected(const bool bIsSelected)
{
	bSelected=bIsSelected;
	OnSelectedStateChanged();
}

void UIndexButtonWithText::OnSelectedStateChanged_Implementation()
{
}

void UIndexButtonWithText::HandleButtonClicked()
{
	OnButtonClicked.Broadcast(Index);
}
