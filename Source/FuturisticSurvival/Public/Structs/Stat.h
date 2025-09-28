// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Current = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Max = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float PerSecondTick = 1.f;

public:

	FStat()
	{
	}
	FStat(const float& current, const float& max, const float& tick)
	{
		Current = current;
		Max = max;
		PerSecondTick = tick;
	}

	void TickStat(const float& DeltaTime)
	{
		Current = FMath::Clamp(Current + (PerSecondTick * DeltaTime), 0.f, Max);
	}

	void Adjust(const float& Amount)
	{
		Current = FMath::Clamp(Current+Amount, 0.f, Max);
	}

	float Percentile() const
	{
		return (Current / Max);
	}

	void AdjustTick(const float& NewTick)
	{
		PerSecondTick = NewTick;
	}

	float GetCurrent() const
	{
		return Current;
	}

	bool HasEnough(const float& Amount = 0) const
	{
		return Current >= Amount;
	}
};