// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "SurvCharacter.h"
#include "SurvEnemyCharacter.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ASurvEnemyCharacter : public ASurvCharacter
{
	GENERATED_BODY()

public:
	ASurvEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

};
