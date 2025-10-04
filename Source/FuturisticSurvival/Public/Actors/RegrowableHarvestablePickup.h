// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Actors/HarvestablePickup.h"
#include "RegrowableHarvestablePickup.generated.h"

/**
 * RegrowableHarvestablePickup actor is for resources than can be harvested with hand and will regrow like a bush
 */
UCLASS()
class FUTURISTICSURVIVAL_API ARegrowableHarvestablePickup : public AHarvestablePickup
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="settings", meta = (AllowPrivateAccess = "true"))
	int NO_DaysToRegrow = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State",SaveGame, meta = (AllowPrivateAccess = "true"))
	int DaysSinceLastHarvest = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="settings", meta = (AllowPrivateAccess = "true"))
	int ItemRegrowthAmount = 1;
	

	void ResetHarvest();

protected:
	virtual void BeginPlay() override;
	

public:

	void OnDayChanged();
	
};
