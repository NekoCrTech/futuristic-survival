// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionInterface.h"
#include "Public/Character/SurvCharacter.h"
#include "SurvPlayerCharacter.generated.h"


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
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

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
#pragma endregion

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void PlayerJump();

	void SprintOn();
	void SprintOff();
	void SneakOn();
	void SneakOff();
	
	void OnInteract();
	
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> InteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	bool bEnableRayTrace = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> InteractableActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* InteractionActor = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Settings", meta = (AllowPrivateAccess = "true"))
	float InteractionTraceLength = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DEBUG", meta = (AllowPrivateAccess = "true"))
	bool DEBUG_INTERACTION_TRACE = false;

	void TraceForInteraction();
	
};
