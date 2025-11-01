// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Abilitysystem/Abilities/SurvGameplayAbility.h"
#include "SurvSearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class UAITask_MoveTo;
class ASurvCharacter;
class USurvWaitGameplayEvent;
class AAIController;
class ASurvEnemyCharacter;
class UAbilityTask_WaitDelay;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvSearchForTarget : public USurvGameplayAbility
{
	GENERATED_BODY()

public:
	USurvSearchForTarget();

	TWeakObjectPtr<ASurvEnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<ASurvCharacter> TargetCharacter;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:

	UPROPERTY()
	TObjectPtr<USurvWaitGameplayEvent> WaitGameplayEventTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;

	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;

	void StartSearch();

	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void Search();

	void MoveToTargetAndAttack();

	UFUNCTION()
	void AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);

	UFUNCTION()
	void Attack();
	
};

