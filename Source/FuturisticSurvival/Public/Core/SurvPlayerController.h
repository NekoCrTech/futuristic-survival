// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API ASurvPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> UIMappingContexts;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
public:
	void SetMovementMappingContextEnabled(bool bEnabled);
	
};
