// developed by Neko


#include "Public/Player/SurvPlayerController.h"

#include <EnhancedInputComponent.h>
#include <GameFramework/PawnMovementComponent.h>

#include "EnhancedInputSubsystems.h"
#include "Character/SurvPlayerCharacter.h"
#include "UserInterface/SurvHUD.h"



void ASurvPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	
	PlayerCharacter = Cast<ASurvPlayerCharacter>(aPawn);
	HUD = Cast<ASurvHUD>(GetHUD());
	if(!HUD)
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"HUD is invalid");
		return;
	}
	HUD->OnHudCreated.AddDynamic(this, &ASurvPlayerController::OnHudCreated);
	HUD->InitializeHUD();
}

void ASurvPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
			for (UInputMappingContext* CurrentContext : UIMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Jumping
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::PlayerJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::SprintOn);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::SprintOff);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ThisClass::SprintOff);
			EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Started, this, &ThisClass::SneakOn);
			EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Completed, this, &ThisClass::SneakOff);
			EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Canceled, this, &ThisClass::SneakOff);
			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
			EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Triggered, this, &ThisClass::Lean);
			EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Canceled, this, &ThisClass::Lean);
			EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Completed, this, &ThisClass::Lean);
			// Interacting
			EnhancedInputComponent->BindAction(InteractAction,ETriggerEvent::Completed, this, &ThisClass::OnInteract);
			// Abilities
			EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::OnPrimary);
			EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &ThisClass::OnSecondary);
			// Camera
			EnhancedInputComponent->BindAction(TogglePerspectiveAction,ETriggerEvent::Started,this, &ThisClass::TogglePerspective);
			// User Interface
			EnhancedInputComponent->BindAction(TogglePlayerWindowAction,ETriggerEvent::Started, this, &ThisClass::TogglePlayerWindow);
			EnhancedInputComponent->BindAction(TogglePlacementWindowAction,ETriggerEvent::Started, this, &ThisClass::TogglePlacementWindow);
			// Building Mode
			EnhancedInputComponent->BindAction(PlaceAction,ETriggerEvent::Started,this,&ThisClass::OnPlaceBuilding);
			EnhancedInputComponent->BindAction(RotateAction,ETriggerEvent::Started,this,&ThisClass::OnRotateBuilding);
			EnhancedInputComponent->BindAction(CancelPlacementAction,ETriggerEvent::Started,this,&ThisClass::OnCancelPlacement);
		}
	}
}

void ASurvPlayerController::SetMovementMappingContextEnabled(bool bEnabled)
{
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			if (bEnabled)
			{
				for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
				return;
			}
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->RemoveMappingContext(CurrentContext);
			}
		}
	}
}

void ASurvPlayerController::SetBuildingMappingContextEnabled(bool bEnabled)
{if (IsLocalPlayerController())
{
	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bEnabled)
		{
			Subsystem->AddMappingContext(BuildingMappingContext, 10);
			return;
		}
		Subsystem->RemoveMappingContext(BuildingMappingContext);
	}
}
}

//---------------------------------------------------------------------
/**							Input handlers							**/
//---------------------------------------------------------------------

void ASurvPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void ASurvPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ASurvPlayerController::Lean(const FInputActionValue& Value)
{
	if (!PlayerCharacter->IsInFirstPerson()) return;
	PlayerCharacter->SetLeanAmount(Value.Get<float>());
}

void ASurvPlayerController::PlayerJump()
{
	if (PlayerCharacter->CanCharJump() && !PlayerCharacter->GetMovementComponent()->IsFalling())
	{
		PlayerCharacter->HasJumped();
	}
}

void ASurvPlayerController::StopJumping()
{
	PlayerCharacter->StopJumping();
}

void ASurvPlayerController::SprintOn()
{
	PlayerCharacter->SetSprinting(true);
}

void ASurvPlayerController::SprintOff()
{
	PlayerCharacter->SetSprinting(false);
}

void ASurvPlayerController::SneakOn()
{
	PlayerCharacter->SetSneaking(true);
	PlayerCharacter->Crouch();
}

void ASurvPlayerController::SneakOff()
{
	PlayerCharacter->SetSneaking(false);
	PlayerCharacter->UnCrouch();
}

void ASurvPlayerController::OnInteract()
{
	PlayerCharacter->HandleInteract();
}

void ASurvPlayerController::OnPrimary()
{
	PlayerCharacter->ActivatePrimaryAbility();
}

void ASurvPlayerController::OnSecondary()
{
	PlayerCharacter->ActivateSecondaryAbility();
}

void ASurvPlayerController::TogglePerspective()
{
	PlayerCharacter->HandleTogglePerspective();
}

// User Interface Handlers

void ASurvPlayerController::TogglePlayerWindow()
{
	HandleTogglePlayerWindow();
}

void ASurvPlayerController::TogglePlacementWindow()
{
	if(bInventoryIsShown)
	{
		TogglePlayerWindow();
	}
	bInBuildingModeUI = !bInBuildingModeUI;
	SetMovementMappingContextEnabled(!bInBuildingModeUI);
	//TODO: Toggle Building Mode UI in BP
}

// Building Mode Handlers

void ASurvPlayerController::OnRotateBuilding(const FInputActionValue& Value)
{
	float Rotation = Value.Get<float>();
	PlayerCharacter->HandleRotateBuilding(Rotation>0);
}

void ASurvPlayerController::OnPlaceBuilding()
{
	PlayerCharacter->HandlePlaceBuilding();
}

void ASurvPlayerController::OnCancelPlacement()
{
	PlayerCharacter->HandleCancelPlacement();
}


//---------------------------------------------------------------------
/**								Utilities							**/
//---------------------------------------------------------------------

void ASurvPlayerController::HandleTogglePlayerWindow(bool bUseOtherInventory)
{
	if(bInBuildingModeUI)
	{
		TogglePlacementWindow();
	}
	bInventoryIsShown = !bInventoryIsShown;
	
	HUD->ToggleCharacterWindow(bUseOtherInventory);
}

void ASurvPlayerController::TogglePlacementMode()
{
	if(bInBuildingModeUI)
	{
		TogglePlacementWindow();
		bInBuildingModePlacement = true;
		SetBuildingMappingContextEnabled(true);
		return;
	}
	bInBuildingModePlacement = false;
	SetBuildingMappingContextEnabled(false);
}

void ASurvPlayerController::OnHudCreated()
{
	PlayerCharacter->CreateInventory();
}




