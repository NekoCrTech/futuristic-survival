// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SurvGameMode.generated.h"

class AChronomanager;
/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API ASurvGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void InitializeChronomanager();

	UFUNCTION(BlueprintCallable)
	AChronomanager* GetChronomanager() const { return Chronomanager; }
	

private:


	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	AChronomanager* Chronomanager;
	
};
