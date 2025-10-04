// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Save/SaveActorInterface.h"
#include "SurvCharacter.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ASurvCharacter : public ACharacter, public ISaveActorInterface
{
	GENERATED_BODY()

public:
	
	ASurvCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual FGuid GetActorSaveID_Implementation() override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void SetActorGUID_Implementation(const FGuid& NewGiud);

	void SetWasSpawned(bool IsSpawned);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	FGuid SaveActorID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	bool bWasSpawned = false;
	
	virtual void BeginPlay() override;

	bool CanCharJump() const;
	void HasJumped();

	bool CanSprint() const;
	void SetSprinting(const bool& IsSprinting);
	void SetSneaking(const bool& IsSneaking);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	 TObjectPtr<class UStatlineComponent> Statline;

	

};
