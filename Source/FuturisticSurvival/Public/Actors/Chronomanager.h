// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Structs/TimeData.h"
#include "Enums/DayLength.h"
#include "Chronomanager.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API AChronomanager : public ASurvActor
{
	GENERATED_BODY()
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Use day/night cycle"))
	bool bUseDayNightCycle = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Current Time of day information"))
	FTimeData CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Day length in minutes"))
	float DayLengthInMinutes = 10.f;
	
	UPROPERTY()
	float TimeDecay = 0.f;
	UPROPERTY()
	float MinuteLength = 0.f;
	UPROPERTY()
	bool bTimeWasUpdated = false;

	void UpdateTime(const float& DeltaTime);
	void AdvanceMinute();
	void AdvanceHour();
	void AdvanceDay();
	void AdvanceMonth();
	void AdvanceYear();

	void CalculateDayLength();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
