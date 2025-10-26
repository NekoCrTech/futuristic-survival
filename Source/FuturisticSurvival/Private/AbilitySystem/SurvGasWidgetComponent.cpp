// developed by Neko


#include "AbilitySystem/SurvGasWidgetComponent.h"

#include "AbilitySystem/SurvAbilitySystemComponent.h"
#include "AbilitySystem/SurvAttributeSet.h"
#include "Character/SurvCharacter.h"

void USurvGasWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		SurvCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAtributeDelegate();
}

void USurvGasWidgetComponent::InitAbilitySystemData()
{
	SurvCharacter = Cast<ASurvCharacter>(GetOwner());
	AttributeSet = Cast<USurvAttributeSet>(SurvCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<USurvAbilitySystemComponent>(SurvCharacter->GetAbilitySystemComponent());
}

bool USurvGasWidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void USurvGasWidgetComponent::InitializeAtributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributeInitialized.AddDynamic(this, &ThisClass::USurvGasWidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void USurvGasWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<USurvAbilitySystemComponent>(ASC);
	AttributeSet = Cast<USurvAttributeSet>(AS);

	if (!IsASCInitialized()) return;
	InitializeAtributeDelegate();
}

void USurvGasWidgetComponent::BindToAttributeChanges()
{
	
}
