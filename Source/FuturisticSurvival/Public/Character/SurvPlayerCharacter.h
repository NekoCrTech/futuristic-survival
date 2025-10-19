// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionInterface.h"
#include "Public/Character/SurvCharacter.h"
#include "SurvPlayerCharacter.generated.h"


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
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UBuildingComponent* GetBuildingComponent() const {return BuildingComponent;}
	
	UFUNCTION(BlueprintNativeEvent)
	void TogglePlayerInventoryBP();
	void TogglePlayerInventory();

	UFUNCTION(BlueprintNativeEvent)
	void ToggleBuildingModeUserInterfaceBP();
	void ToggleBuildingModeUserInterface();

	UFUNCTION(BlueprintNativeEvent)
	void ToggleBuildingModePlacementBP();
	void ToggleBuildingModePlacement();
	

	UFUNCTION()
	void OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateInteractionText();
	void UpdateInteractionText_Implementation();

	

	
protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Input
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* JumpAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;
                 	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* MouseLookAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* SprintAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* SneakAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* TogglePerspectiveAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* BuildingModeAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* LeanAction;
#pragma endregion

#pragma region BuildingInputs
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* PlaceAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* CancelPlacementAction;

#pragma endregion

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Lean(const FInputActionValue& Value);
	

	void PlayerJump();

	void SprintOn();
	void SprintOff();
	void SneakOn();
	void SneakOff();
	
	void OnInteract();

	void TogglePerspective();

	void OnRotateBuilding(const FInputActionValue& Value);
	void OnPlaceBuilding();
	void OnCancelPlacement();
	
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> InteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBuildingComponent> BuildingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	bool bEnableRayTrace = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> InteractableActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* InteractionActor = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Settings", meta = (AllowPrivateAccess = "true"))
	float InteractionTraceLength = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bInventoryIsShown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bInFirstPerson = true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess="true"))
	bool bUseHeadBob = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta = (AllowPrivateAccess = "true"))
	float LeanAmount = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bInBuildingModeUI = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bInBuildingModePlacement = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DEBUG", meta = (AllowPrivateAccess = "true"))
	bool DEBUG_INTERACTION_TRACE = false;

	void TraceForInteraction();
	
};
