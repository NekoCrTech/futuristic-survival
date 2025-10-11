// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Structs/TimeData.h"
#include "Enums/DayLength.h"
#include "Chronomanager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeChangeDelegate, FTimeData, TimeData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTemperatureChangeDelegate, float, CurrentTemp);

UCLASS()
class FUTURISTICSURVIVAL_API AChronomanager : public ASurvActor
{
	GENERATED_BODY()
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Use day/night cycle"))
	bool bUseDayNightCycle = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Current Time of day information"))
	FTimeData CurrentTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Day length in real time minutes", ForceUnits = "min"))
	float DayLengthInMinutes = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Chrono|Time|Debug", meta = (AllowPrivateAccess = "true"))
	int32 StartDay = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Chrono|Time|Debug", meta = (AllowPrivateAccess = "true"))
	int32 StartMonth = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Chrono|Time|Debug", meta = (AllowPrivateAccess = "true"))
	int32 StartYear = 3000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category="Chrono|Time|Debug", meta = (AllowPrivateAccess = "true"))
	bool bUseStartDate = false;
	void SetStartDate();
	

#pragma region Lightning
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = "Reference to the directional light in map"))
	class ADirectionalLight* SunLight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* DailySunlightRotation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* AnnualSunlightRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	class ASkyLight* SkyLight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* SkylightHourlyColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	float MaxSunlightIntensity = 10.f;
	
#pragma endregion

#pragma region Temperature
	
	FTimerHandle WorldTemperatureHandle;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chrono|Temperature", meta = (AllowPrivateAccess = "true", Tooltip = "Seconds between Temprature Updates", Units="s"))
	float WorldTempTickRate = 5;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Chrono|Temperature", meta = (AllowPrivateAccess = "true", Tooltip = "Current ambient Temperature in °F", DisplayName="World Temperature (°F)", ForceUnits = "°F" ))
	float CurrentWorldTemp = 75;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chrono|Temperature", meta = (AllowPrivateAccess = "true", Tooltip = "Daily Temperature Range"))
	UCurveFloat* DailyTemperatureRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chrono|Temperature", meta = (AllowPrivateAccess = "true", Tooltip = "Annual Temperature Range"))
	UCurveFloat* AnnualTemperatureRange;

	
#pragma endregion

	UPROPERTY()
	float TimeDecay = 0.f;
	UPROPERTY()
	float MinuteLength = 0.f;
	UPROPERTY()
	bool bTimeWasUpdated = false;
	UPROPERTY()
	float CurrentTimeOfDay = 0.f;

	void UpdateTime(const float& DeltaTime);
	void AdvanceMinute();
	void AdvanceHour();
	void AdvanceDay();
	void AdvanceMonth();
	void AdvanceYear();
	void SetDayOfYear();

	void CalculateDayLength();
	void UpdateTimeOfDay();

	void UpdateLighting();
	void UpdateLightRotation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateFromSave_Implementation() override;

	FTimeData GetCurrentGameTime() const { return CurrentTime; }

	UPROPERTY(BlueprintAssignable, Category="Chrono|Time")
	FTimeChangeDelegate OnTimeChange;
	UPROPERTY(BlueprintAssignable, Category="Chrono|Temperature")
	FTemperatureChangeDelegate OnTemperatureChange;

	FSaveActorData GetSaveData_Implementation() override;
	void SetActorRawSaveData_Implementation(const TArray<FString>& RawData) override;

	UFUNCTION()
	void UpdateTemperature();
	
};
