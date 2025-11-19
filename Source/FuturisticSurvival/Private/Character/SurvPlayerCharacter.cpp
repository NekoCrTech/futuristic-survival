// developed by Neko


#include "Public/Character/SurvPlayerCharacter.h"

#include "AbilitySystemComponent.h"
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
#include "AbilitySystem/SurvAttributeSet.h"
#include "BuildingSystem/BuildingComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "UserInterface/SurvHUD.h"
#include "Player/SurvPlayerController.h"
#include "GameplayTags/SurvTags.h"
#include "InventorySystem/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SurvPlayerState.h"

ASurvPlayerCharacter::ASurvPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

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
	
	// Create Inventory Scene Capture
	InventorySceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Inventory Scene Capture"));
	InventorySceneCapture->SetupAttachment(RootComponent);
	InventorySceneCapture->SetRelativeLocation(FVector(150.f,0.f,0.f));
	InventorySceneCapture->SetRelativeRotation(FRotator(0.f,-180.f,0.f));
	InventorySceneCapture->ShowOnlyActorComponents(this);

	//Create Building Component
	BuildingComponent = CreateDefaultSubobject<UBuildingComponent>(TEXT("Building Component"));

	Tags.Add(SurvivalTags::Player);
	Tags.Add(SurvivalTags::DamageCauser);
}

void ASurvPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(),this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();
	
	USurvAttributeSet* SurvAttributeSet = Cast<USurvAttributeSet>(GetAttributeSet());
	if (!IsValid(SurvAttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(SurvAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void ASurvPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(),this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());

	USurvAttributeSet* SurvAttributeSet = Cast<USurvAttributeSet>(GetAttributeSet());
	if (!IsValid(SurvAttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(SurvAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
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
		UpdateInteractionText();
		InteractionActor = nullptr;
		return;
	}
	InteractionActor = LTHit.GetActor();
	UpdateInteractionText();
}

//------------------------
// Gameplay Ability System
//------------------------

void ASurvPlayerCharacter::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if(!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

UAbilitySystemComponent* ASurvPlayerCharacter::GetAbilitySystemComponent() const
{
	ASurvPlayerState* SurvPlayerState = Cast<ASurvPlayerState>(GetPlayerState());
	if (!IsValid(SurvPlayerState)) return nullptr;
	
	return SurvPlayerState->GetAbilitySystemComponent();
}

UAttributeSet* ASurvPlayerCharacter::GetAttributeSet() const
{
	ASurvPlayerState* SurvPlayerState = Cast<ASurvPlayerState>(GetPlayerState());
	if (!IsValid(SurvPlayerState)) return nullptr;
	
	return SurvPlayerState->GetAttributeSet();
}

//------------------
// Actions on Inputs
//------------------

void ASurvPlayerCharacter::HandleInteract()
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

void ASurvPlayerCharacter::HandleTogglePerspective()
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

// Ability Actions

void ASurvPlayerCharacter::ActivatePrimaryAbility() const
{
	ActivateAbility(SurvTags::SurvAbilities::Primary);
}

void ASurvPlayerCharacter::ActivateSecondaryAbility() const
{
	ActivateAbility(SurvTags::SurvAbilities::Secondary);
}

// Building Actions

void ASurvPlayerCharacter::HandleRotateBuilding(const bool& bRotateRight)
{
	BuildingComponent->RotatePlacement(bRotateRight);
}

void ASurvPlayerCharacter::HandlePlaceBuilding()
{
	BuildingComponent->Place();
}

void ASurvPlayerCharacter::HandleCancelPlacement()
{
	BuildingComponent->CancelPlacement();
}

// Inventory

void ASurvPlayerCharacter::InitializeComponents()
{
	Inventory->CreateInventoryWidget();
	BuildingComponent->InitializeBuildingComponent();
}

