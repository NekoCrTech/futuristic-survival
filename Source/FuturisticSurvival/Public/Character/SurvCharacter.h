// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Save/SaveActorInterface.h"
#include "AbilitySystemInterface.h"
#include "SurvCharacter.generated.h"

struct FOnAttributeChangeData;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UInventoryComponent;
class UStatlineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS()
class FUTURISTICSURVIVAL_API ASurvCharacter : public ACharacter, public ISaveActorInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ASurvCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const {return nullptr;}
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

	virtual FGuid GetActorSaveID_Implementation() override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void SetActorGUID_Implementation(const FGuid& NewGiud) override;

	void SetWasSpawned(const bool& IsSpawned);

	UFUNCTION(BlueprintCallable)
	UStatlineComponent* GetStatline() const {return Statline;}
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventory() const {return Inventory;}

	bool IsAlive() const {return bAlive;}
	void SetAlive(const bool& bAliveStatus) { bAlive = bAliveStatus; }

	UFUNCTION(BlueprintCallable, Category = "Survival|Death")
	virtual void HandleRespawn();

	UFUNCTION(BlueprintCallable, Category = "Survival|Death")
	void ResetAttributes();

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
	void InitializeAttributes() const;

	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleDeath();	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStatlineComponent> Statline;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Abilities", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Survival|Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Survival|Abilities", meta = (AllowPrivateAccess = "true"),Replicated)
	bool bAlive = true;

};
