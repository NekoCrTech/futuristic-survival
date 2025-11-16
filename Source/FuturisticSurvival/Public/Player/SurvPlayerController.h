// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvPlayerController.generated.h"

class ASurvHUD;
class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API ASurvPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	
	void SetMovementMappingContextEnabled(bool bEnabled);
	void SetBuildingMappingContextEnabled(bool bEnabled);
	
#pragma region Input
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* JumpAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;
                 	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* MouseLookAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* SprintAction;
                 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* SneakAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* LeanAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* PrimaryAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Character", meta=(AllowPrivateAccess="true"))
	UInputAction* SecondaryAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Camera", meta=(AllowPrivateAccess="true"))
	UInputAction* TogglePerspectiveAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|UserInterface", meta=(AllowPrivateAccess="true"))
	UInputAction* TogglePlacementWindowAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|UserInterface", meta=(AllowPrivateAccess="true"))
	UInputAction* TogglePlayerWindowAction;

#pragma endregion
	
#pragma region BuildingInputs
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Building", meta=(AllowPrivateAccess="true"))
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Building", meta=(AllowPrivateAccess="true"))
	UInputAction* PlaceAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Survival|Input|Building", meta=(AllowPrivateAccess="true"))
	UInputAction* CancelPlacementAction;

#pragma endregion
	
protected:
	virtual void OnPossess(APawn* aPawn) override;
	
private:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> UIMappingContexts;

	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* BuildingMappingContext;
	
	/** References */	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Survival|References", meta=(AllowPrivateAccess="true"))
	class ASurvPlayerCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Survival|References", meta=(AllowPrivateAccess="true"))
	ASurvHUD* HUD;
	
	/** State */	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Survival|State", meta=(AllowPrivateAccess="true"))
	bool bInBuildingModeUI = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Survival|State", meta=(AllowPrivateAccess="true"))
	bool bInBuildingModePlacement = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Survival|State", meta=(AllowPrivateAccess="true"))
	bool bInventoryIsShown = false;
	
	/** Utilities */
	void HandleTogglePlayerWindow(bool bUseOtherInventory = false);
	void TogglePlacementMode();
	
	/** Input handlers **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Lean(const FInputActionValue& Value);
	void PlayerJump();
	void StopJumping();
	void SprintOn();
	void SprintOff();
	void SneakOn();
	void SneakOff();
	void OnInteract();
	void OnPrimary();
	void OnSecondary();
	void TogglePerspective();
	
	void TogglePlayerWindow();
	void TogglePlacementWindow();

	void OnRotateBuilding(const FInputActionValue& Value);
	void OnPlaceBuilding();
	void OnCancelPlacement();
	
};
