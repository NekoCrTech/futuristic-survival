// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "SurvCharacter.h"
#include "SurvEnemyCharacter.generated.h"

class USurvAttributeSet;
class USurvAbilitySystemComponent;

UCLASS()
class FUTURISTICSURVIVAL_API ASurvEnemyCharacter : public ASurvCharacter
{
	GENERATED_BODY()

public:
	ASurvEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USurvAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USurvAttributeSet> AttributeSet;

};
