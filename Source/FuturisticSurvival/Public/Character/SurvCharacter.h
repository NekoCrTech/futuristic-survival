// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Save/SaveActorInterface.h"
#include "AbilitySystemInterface.h"
#include "SurvCharacter.generated.h"

class UGameplayAbility;
class UInventoryComponent;
class UStatlineComponent;

UCLASS()
class FUTURISTICSURVIVAL_API ASurvCharacter : public ACharacter, public ISaveActorInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ASurvCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual FGuid GetActorSaveID_Implementation() override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void SetActorGUID_Implementation(const FGuid& NewGiud) override;

	void SetWasSpawned(const bool& IsSpawned);

	UFUNCTION(BlueprintCallable)
	UStatlineComponent* GetStatline() const {return Statline;}
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventory() const {return Inventory;}

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInventoryComponent> Inventory;

	void GiveStartupAbilities();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStatlineComponent> Statline;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Abilities", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	
	

	

};
