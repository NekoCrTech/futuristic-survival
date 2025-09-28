// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/StatEnum.h"
#include "Structs/Stat.h"
#include "StatlineComponent.generated.h"


class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UStatlineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatlineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMovementCompReference(UCharacterMovementComponent* Comp);

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const EStat Stat) const;

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

protected:
	virtual void BeginPlay() override;

private:

	UCharacterMovementComponent* OwningCharMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Energy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Thirst = FStat(100,100,-0.25);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Stats")
	FStat Hunger = FStat(100,100,-0.125);
	

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
		
};
