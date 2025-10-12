// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/StatEnum.h"
#include "Save/SaveActorInterface.h"
#include "Structs/SaveActorData.h"
#include "Structs/Stat.h"
#include "StatlineComponent.generated.h"


class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UStatlineComponent : public UActorComponent, public ISaveActorInterface
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UCharacterMovementComponent* OwningCharMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Energy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Thirst = FStat(100,100,-0.25);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Hunger = FStat(100,100,-0.125);
	
#pragma region StalineSettings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float JumpCost = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float SprintCostMultiplier = 2.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float WalkSpeed = 125.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float SprintSpeed = 450.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float SneakSpeed = 125.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float StaminaExhaustionDuration = 5.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float HungerDps = 5.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Settings")
	float ThirstDps = 2.f;
#pragma endregion

#pragma region Temperature
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	bool bUseTemperature = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float CurrentAmbientTemperature=0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float CurrentLocalTempOffset = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float CurrentBodyTemperature = 98.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float HeatInsulation = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float ColdInsulation = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float BodyCoverage = 0.f; // Has a value from 0 to 8
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float AdjustmentFactor = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float TempDiffToIgnore = 5.f;

	void UpdateBodyTemperature(const float& DeltaTime);
	
#pragma endregion
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	bool bIsSprinting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	bool bIsSneaking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="State")
	float CurrentStaminaExhaustion = 0.f;
	
		
	void TickStats(const float& DeltaTime);
	void TickStamina(const float& DeltaTime);
	void TickThirst(const float& DeltaTime);
	void TickHunger(const float& DeltaTime);
	bool IsValidSprinting();

protected:
	virtual void BeginPlay() override;

public:	
	UStatlineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMovementCompReference(UCharacterMovementComponent* Comp);

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const EStat Stat) const;

	UFUNCTION(BlueprintCallable)
	void AdjustStat(const EStat& Stat, const float& Amount);

	UFUNCTION(BlueprintCallable)
	bool CanSprint()const;
	UFUNCTION(BlueprintCallable)
	void SetSprinting(const bool IsSprinting);
	UFUNCTION(BlueprintCallable)
	void SetSneaking(const bool IsSneaking);
	UFUNCTION(BlueprintCallable)
	bool CanJump();
	UFUNCTION(BlueprintCallable)
	void HasJumped();

	UFUNCTION()
	void OnWorldTempChange(float Temperature);

	UFUNCTION(BlueprintCallable)
	void AdjustLocalTempOffset(const float& OffsetValue);
	UFUNCTION(BlueprintCallable)
	void AdjustHeatInsulation(const float& Amount);
	UFUNCTION(BlueprintCallable)
	void AdjustColdInsulation(const float& Amount);
	UFUNCTION(BlueprintCallable)
	void AdjustBodyCoverage(const float& Amount);

	virtual FSaveComponentData GetSaveComponentData_Implementation();
	virtual void SetSaveComponentData_Implementation(FSaveComponentData Data);
	
};
