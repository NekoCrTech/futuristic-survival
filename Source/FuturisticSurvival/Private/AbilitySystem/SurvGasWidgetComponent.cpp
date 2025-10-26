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
	}
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

void USurvGasWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<USurvAbilitySystemComponent>(ASC);
	AttributeSet = Cast<USurvAttributeSet>(AS);
}
