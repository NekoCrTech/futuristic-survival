// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Actors/HarvestablePickup.h"
#include "Structs/TimeData.h"
#include "RegrowableHarvestablePickup.generated.h"


class AChronomanager;
/**
 * RegrowableHarvestablePickup actor is for resources than can be harvested with hand and will regrow like a bush
 *
 * CAUTION! PermanentMesh Should not be empty because it will be considered as one time harvestable and will be destroyed after harvest
 * TODO: Find a better way for this check in AHarvestablePickup
 */
UCLASS()
class FUTURISTICSURVIVAL_API ARegrowableHarvestablePickup : public AHarvestablePickup
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AChronomanager* TimeManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="settings", meta = (AllowPrivateAccess = "true"))
	int NO_DaysToRegrow = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State",SaveGame, meta = (AllowPrivateAccess = "true"))
	int DaysSinceLastHarvest = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="settings", meta = (AllowPrivateAccess = "true"))
	int ItemRegrowthAmount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	FTimeData HarvestTracking;

	void ResetHarvest();

protected:
	virtual void BeginPlay() override;
	

public:

	void OnDayChanged();

	UFUNCTION()
	void OnTimeChanged(FTimeData TimeData);

	virtual void Interact_Implementation(class ASurvCharacter* Caller) override;
};
