// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Structs/TimeData.h"
#include "Enums/DayLength.h"
#include "Chronomanager.generated.h"



UCLASS()
class FUTURISTICSURVIVAL_API AChronomanager : public ASurvActor
{
	GENERATED_BODY()
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Use day/night cycle"))
	bool bUseDayNightCycle = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Current Time of day information"))
	FTimeData CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category="Chrono|Time", meta = (AllowPrivateAccess = "true", Tooltip = "Day length in real time minutes"))
	float DayLengthInMinutes = 10.f;

#pragma region Lightning
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = "Reference to the directional light in map"))
	class ADirectionalLight* SunLight;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveFloat* DailySunlightIntensity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveFloat* AnnualSunlightIntensity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* DailySunlightRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* AnnualSunlightRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	class ASkyLight* SkyLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveFloat* SkylightIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	UCurveLinearColor* SkylightHourlyColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chrono|Lighting", meta = (AllowPrivateAccess = "true", Tooltip = ""))
	float MaxSunlightIntensity = 10.f;
	
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
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateFromSave_Implementation() override;
};
