// developed by Neko


#include "AbilitySystem/Tasks/SurvAttributeChangeTask.h"

#include "AbilitySystemComponent.h"

USurvAttributeChangeTask* USurvAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent,
                                                                             FGameplayAttribute Attribute)
{
	USurvAttributeChangeTask* WaitForAttributeChangeTask = NewObject<USurvAttributeChangeTask>();
	WaitForAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;

	if(!IsValid(AbilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &USurvAttributeChangeTask::AttributeChanged);

	return WaitForAttributeChangeTask;
}

void USurvAttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void USurvAttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
