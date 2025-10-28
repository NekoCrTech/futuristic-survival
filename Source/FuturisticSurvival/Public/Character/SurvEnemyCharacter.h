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
	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|AI")
	float AcceptanceRadius{500.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|AI")
	float MinAttackDelay{.1f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|AI")
	float MaxAttackDelay{.5f};
	

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USurvAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USurvAttributeSet> AttributeSet;

};
