// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Logger.h"
#include "TimeData.generated.h"

USTRUCT(BlueprintType)
struct FTimeData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 DayOfYear = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 Year = 3000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 Month = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 Day = 31;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 Hour = 10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	int32 Minute = 0;

	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FTimeData& Struct)
	{
		Ar << Struct.DayOfYear;
		Ar << Struct.Year;
		Ar << Struct.Month;
		Ar << Struct.Day;
		Ar << Struct.Hour;
		Ar << Struct.Minute;
		
		return Ar;
	}

	FString GetSaveString() const
	{
		FString Ret = FString::FromInt(DayOfYear);
		Ret += "|";
		Ret += FString::FromInt(Year);
		Ret += "|";
		Ret += FString::FromInt(Month);
		Ret += "|";
		Ret += FString::FromInt(Day);
		Ret += "|";
		Ret += FString::FromInt(Hour);
		Ret += "|";
		Ret += FString::FromInt(Minute);
		return Ret;
	}

	void UpdateFromSaveString(TArray<FString> Parts)
	{
		if (Parts.Num() != 6)
		{
			Logger::GetInstance()->AddMessage("FTimeData::UpdateFromSaveString called with other than 6 parts", ERRORLEVEL::EL_WARNING);
			return;
		}
		DayOfYear = FCString::Atof(*Parts[0]);
		Year = FCString::Atof(*Parts[1]);
		Month = FCString::Atof(*Parts[2]);
		Day = FCString::Atof(*Parts[3]);
		Hour = FCString::Atof(*Parts[4]);
		Minute = FCString::Atof(*Parts[5]);
	}
	
};
