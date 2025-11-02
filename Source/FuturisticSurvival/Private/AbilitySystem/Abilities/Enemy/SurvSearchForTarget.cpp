// developed by Neko


#include "AbilitySystem/Abilities/Enemy/SurvSearchForTarget.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AIController.h"
#include "AbilitySystem/AbilityTasks/SurvWaitGameplayEvent.h"
#include "Character/SurvEnemyCharacter.h"
#include "GameplayTags/SurvTags.h"
#include "Tasks/AITask_MoveTo.h"
#include "Tools/SurvBlueprintLibrary.h"

USurvSearchForTarget::USurvSearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void USurvSearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwningEnemy = Cast<ASurvEnemyCharacter>(GetAvatarActorFromActorInfo());
	check(OwningEnemy.IsValid());
	OwningAIController = Cast<AAIController>(OwningEnemy->GetController());
	check(OwningAIController.IsValid());

	StartSearch();

	WaitGameplayEventTask = USurvWaitGameplayEvent::WaitGameplayEventToActorProxy(GetAvatarActorFromActorInfo(),SurvTags::Events::Enemy::EndAttack);
	WaitGameplayEventTask->EventReceived.AddDynamic(this,&ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
}

void USurvSearchForTarget::StartSearch()
{
	DrawDebugMessage("Start Search");
	if (!OwningEnemy.IsValid()) return;

	const float SearchDelay = FMath::RandRange(OwningEnemy->MinAttackDelay,OwningEnemy->MaxAttackDelay);
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(this,SearchDelay);
	SearchDelayTask->OnFinish.AddDynamic(this,&ThisClass::Search);
	SearchDelayTask->Activate();
}

void USurvSearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	StartSearch();
}

void USurvSearchForTarget::Search()
{
	const FVector SearchOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	FClosestActorWithTagResult ClosestActorWithTagResult = USurvBlueprintLibrary::FindClosestActorWithTag(this, SearchOrigin, SurvivalTags::Player);

	TargetCharacter = Cast<ASurvCharacter>(ClosestActorWithTagResult.Actor);

	if (!TargetCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	if (TargetCharacter->IsAlive())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

void USurvSearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemy.IsValid() || !OwningAIController.IsValid() || !TargetCharacter.IsValid())return;
	if (!OwningEnemy->IsAlive())
	{
		StartSearch();
		return;
	}

	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(OwningAIController.Get(),FVector(),TargetCharacter.Get(), OwningEnemy->AcceptanceRadius);
	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this, &ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
}

void USurvSearchForTarget::AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (Result != EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	OwningEnemy->RotateToTarget(TargetCharacter.Get());
	
	AttackDelayTask = UAbilityTask_WaitDelay::WaitDelay(this,OwningEnemy->GetTimelineLength());
	AttackDelayTask->OnFinish.AddDynamic(this,&ThisClass::Attack);
	AttackDelayTask->Activate();
}

void USurvSearchForTarget::Attack()
{
	const FGameplayTag AttackTag = SurvTags::SurvAbilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}
