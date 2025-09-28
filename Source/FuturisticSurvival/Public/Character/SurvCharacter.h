// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvCharacter.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ASurvCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASurvCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	bool CanJump() const;
	void HasJumped();

	bool CanSprint() const;
	void SetSprinting(const bool& IsSprinting);
	void SetSneaking(const bool& IsSneaking);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	 TObjectPtr<class UStatlineComponent> Statline;

};
