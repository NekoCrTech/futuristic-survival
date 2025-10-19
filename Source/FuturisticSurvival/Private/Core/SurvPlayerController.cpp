// developed by Neko


#include "Public/Core/SurvPlayerController.h"

#include "EnhancedInputSubsystems.h"

void ASurvPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
