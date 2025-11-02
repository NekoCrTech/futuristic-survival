// developed by Neko


#include "AbilitySystem/AbilityTasks/SurvWaitGameplayEvent.h"

USurvWaitGameplayEvent* USurvWaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor, FGameplayTag EventTag, bool OnlyTriggerOnce,
	bool OnlyMatchExact)
{
	USurvWaitGameplayEvent* MyObj = NewObject<USurvWaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void USurvWaitGameplayEvent::StartActivation()
{
	Activate();
}
