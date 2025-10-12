// developed by Neko


#include "Public/Character/SurvPlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "FuturisticSurvival.h"
#include "Interaction/InteractionInterface.h"
#include "Components/SphereComponent.h"
#include "Logger.h"
#include "Core/SurvPlayerController.h"
#include "Kismet/GameplayStatics.h"

ASurvPlayerCharacter::ASurvPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create first person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), "head");
	FirstPersonCamera->SetRelativeRotation(FRotator(0,-90,90));
	FirstPersonCamera->SetRelativeLocation(FVector(15,20,2.5));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->Deactivate();
	
	// Create Interaction Trigger
	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Trigger Volume"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetRelativeScale3D(FVector(10.f));
	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASurvPlayerCharacter::OnInteractionTriggerOverlapBegin);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &ASurvPlayerCharacter::OnInteractionTriggerOverlapEnd);
}

void ASurvPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SaveActorID.Invalidate();

	if (!bUseHeadBob)
	{
		// TODO: Implement logic for HeadBob
	}
}

void ASurvPlayerCharacter::Tick(float DeltaTime)
{
	if(bEnableRayTrace)
	{
		TraceForInteraction();
	}
}

void ASurvPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASurvPlayerCharacter::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASurvPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASurvPlayerCharacter::SprintOn);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASurvPlayerCharacter::SprintOff);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ASurvPlayerCharacter::SprintOff);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Started, this, &ASurvPlayerCharacter::SneakOn);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Completed, this, &ASurvPlayerCharacter::SneakOff);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Canceled, this, &ASurvPlayerCharacter::SneakOff);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASurvPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ASurvPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Triggered, this, &ASurvPlayerCharacter::Lean);
		EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Canceled, this, &ASurvPlayerCharacter::Lean);
		EnhancedInputComponent->BindAction(LeanAction,ETriggerEvent::Completed, this, &ASurvPlayerCharacter::Lean);
		// Interacting
		EnhancedInputComponent->BindAction(InteractAction,ETriggerEvent::Completed, this, &ASurvPlayerCharacter::OnInteract);
		// Camera
		EnhancedInputComponent->BindAction(TogglePerspectiveAction,ETriggerEvent::Started,this, &ASurvPlayerCharacter::TogglePerspective);
		// User Interface
		EnhancedInputComponent->BindAction(InventoryAction,ETriggerEvent::Started, this, &ASurvPlayerCharacter::TogglePlayerInventory);
	}
}

//-------------------
// Interaction System
//-------------------

void ASurvPlayerCharacter::OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UInteractionInterface>())
	{
		return;
	}
	InteractableActors.Add(OtherActor);
	bEnableRayTrace = true;
}

void ASurvPlayerCharacter::OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UInteractionInterface>())
	{
		return;
	}
	InteractableActors.Remove(OtherActor);
	bEnableRayTrace = InteractableActors.Num() > 0;
	if (!bEnableRayTrace)
	{
		TraceForInteraction();
		UpdateInteractionText_Implementation(); 
	}
}

void ASurvPlayerCharacter::UpdateInteractionText_Implementation()
{
	UpdateInteractionText();
}

void ASurvPlayerCharacter::TraceForInteraction()
{
	FCollisionQueryParams LTParams = FCollisionQueryParams(FName(TEXT("InteractionTrace")), true, this);
	LTParams.bReturnPhysicalMaterial = false;
	LTParams.bReturnFaceIndex = false;

	//GetWorld()->DebugDrawTraceTag = DEBUG_INTERACTION_TRACE ? TEXT("InteractionTrace") : TEXT("NONE");

	
	FHitResult LTHit(ForceInit);

	FVector LTStart = bInFirstPerson ? FirstPersonCamera->GetComponentLocation() : FollowCamera->GetComponentLocation();
	float SearchLength = bInFirstPerson ? FirstPersonCamera->GetComponentLocation().Length() :
		(FollowCamera->GetComponentLocation() - CameraBoom->GetComponentLocation()).Length();
	SearchLength += InteractionTraceLength;
	FVector LTEnd = (FollowCamera->GetForwardVector() * SearchLength)+LTStart;
	
	GetWorld()->LineTraceSingleByChannel(LTHit, LTStart, LTEnd, ECC_Visibility, LTParams);

	
	if(!LTHit.bBlockingHit || !LTHit.GetActor()->Implements<UInteractionInterface>())
	{
		UpdateInteractionText_Implementation();
		InteractionActor = nullptr;
		return;
	}
	InteractionActor = LTHit.GetActor();
	UpdateInteractionText_Implementation();
}

//------------------
// Actions on Inputs
//------------------

void ASurvPlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ASurvPlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ASurvPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	DoMove(MovementVector.X, MovementVector.Y);
}

void ASurvPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ASurvPlayerCharacter::Lean(const FInputActionValue& Value)
{
	if (!bInFirstPerson)
	{
		return;
	}
	LeanAmount = Value.Get<float>();
}


void ASurvPlayerCharacter::PlayerJump()
{
	if (CanCharJump() && !GetMovementComponent()->IsFalling())
	{
		HasJumped();
	}
}

void ASurvPlayerCharacter::SprintOn()
{
	SetSprinting(true);
}

void ASurvPlayerCharacter::SprintOff()
{
	SetSprinting(false);
}

void ASurvPlayerCharacter::SneakOn()
{
	SetSneaking(true);
	Crouch();
}

void ASurvPlayerCharacter::SneakOff()
{
	SetSneaking(false);
	UnCrouch();
}

void ASurvPlayerCharacter::OnInteract()
{
	if(InteractionActor == nullptr)
	{
		return;
	}
	IInteractionInterface* Inter = Cast<IInteractionInterface>(InteractionActor);
	if(Inter == nullptr)
	{
		Logger::GetInstance()->AddMessage("ASurvPlayerCharacter::OnInteract - Failed to cast to InteractionInterface", EErrorLevel::EL_ERROR);
		return;
	}
	//Inter->Interact_Implementation(this);
	Inter->Execute_Interact(InteractionActor, this);
	Inter->Execute_SetInteractionWidgetIsEnabled(InteractionActor, false);
	UpdateInteractionText_Implementation();
	
}

void ASurvPlayerCharacter::TogglePerspective()
{
	bInFirstPerson = !bInFirstPerson;
	if(!bInFirstPerson)
	{
		
		FirstPersonCamera->Deactivate();
		FollowCamera->Activate();
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
		return;

	}
	FollowCamera->Deactivate();
	FirstPersonCamera->Activate();
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	return;
}

void ASurvPlayerCharacter::TogglePlayerInventoryBP_Implementation()
{
	// This is used if there is no function override in blueprints 
}

void ASurvPlayerCharacter::TogglePlayerInventory()
{
	bInventoryIsShown = !bInventoryIsShown;
	ASurvPlayerController* MyPC = Cast<ASurvPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MyPC->SetMovementMappingContextEnabled(!bInventoryIsShown);
	TogglePlayerInventoryBP();
}


