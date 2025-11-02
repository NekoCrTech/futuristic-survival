// developed by Neko


#include "AbilitySystem/SurvGasWidgetComponent.h"

#include "AbilitySystem/SurvAbilitySystemComponent.h"
#include "AbilitySystem/SurvAttributeSet.h"
#include "AbilitySystem/UserInterface/SurvAttributeWidget.h"
#include "Blueprint/WidgetTree.h"
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
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair);

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void USurvGasWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	USurvAttributeWidget* AttributeWidget = Cast<USurvAttributeWidget>(WidgetObject);
	if(!IsValid(AttributeWidget)) return;
	if(!AttributeWidget->MatchesAttributes(Pair)) return;

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& Data)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());
	});
}
