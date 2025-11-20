// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Public/Character/SurvCharacter.h"
#include "SurvPlayerCharacter.generated.h"


struct FGameplayTag;
class UBuildingComponent;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;


UCLASS()
class FUTURISTICSURVIVAL_API ASurvPlayerCharacter : public ASurvCharacter
{
	GENERATED_BODY()
public:
	ASurvPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	bool IsInFirstPerson() const {return bInFirstPerson;}
	void SetLeanAmount(float NewLeanAmount) {LeanAmount = NewLeanAmount;}
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UBuildingComponent* GetBuildingComponent() const {return BuildingComponent;}
	
	UFUNCTION()
	void OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateInteractionText();
	
	void HandleInteract();
	void HandleTogglePerspective();
	
	void ActivatePrimaryAbility() const;
	void ActivateSecondaryAbility() const;
	
	void HandleRotateBuilding(const bool& bRotateRight);
	void HandlePlaceBuilding();
	void HandleCancelPlacement();
	void InitializeComponents();
	
protected:
	
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneCaptureComponent2D> InventorySceneCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> InteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBuildingComponent> BuildingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Survival|Interaction", meta = (AllowPrivateAccess = "true"))
	bool bEnableRayTrace = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Survival|Interaction", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> InteractableActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Survival|Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* InteractionActor = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Survival|Interaction|Settings", meta = (AllowPrivateAccess = "true"))
	float InteractionTraceLength = 200.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Survival|State", meta = (AllowPrivateAccess = "true"))
	bool bInFirstPerson = true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|State", meta=(AllowPrivateAccess="true"))
	bool bUseHeadBob = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Survival|State", meta = (AllowPrivateAccess = "true"))
	float LeanAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DEBUG", meta = (AllowPrivateAccess = "true"))
	bool DEBUG_INTERACTION_TRACE = false;

	void TraceForInteraction();
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
		
};
