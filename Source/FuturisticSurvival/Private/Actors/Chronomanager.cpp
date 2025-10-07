// developed by Neko


#include "Actors/Chronomanager.h"
void AChronomanager::BeginPlay()
{
	Super::BeginPlay();
	CalculateDayLength();
}

void AChronomanager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);
}

void AChronomanager::CalculateDayLength()
{
	MinuteLength = (DayLengthInMinutes*60.f) / 1440.f;
	TimeDecay = MinuteLength;
}

void AChronomanager::UpdateTime(const float& DeltaTime)
{
	TimeDecay -= DeltaTime;
	if (TimeDecay <= 0.0f)
	{
		TimeDecay += MinuteLength;
		AdvanceMinute();
	}
}

void AChronomanager::AdvanceMinute()
{
	bTimeWasUpdated = true;
	CurrentTime.Minute++;
	if (CurrentTime.Minute >= 60)
	{
		CurrentTime.Minute = 0;
		AdvanceHour();
	}
}

void AChronomanager::AdvanceHour()
{
	bTimeWasUpdated = true;
	CurrentTime.Hour++;
	if (CurrentTime.Hour >= 24)
	{
		CurrentTime.Hour = 0;
		AdvanceDay();
	}
}

void AChronomanager::AdvanceDay()
{
	bTimeWasUpdated = true;
	CurrentTime.Day++;
	if (CurrentTime.Day >= FDateTime::DaysInMonth(CurrentTime.Year, CurrentTime.Month))
	{
		CurrentTime.Day = 1;
		AdvanceMonth();
	}
	
}

void AChronomanager::AdvanceMonth()
{
	bTimeWasUpdated = true;
	CurrentTime.Month++;
	if (CurrentTime.Month >= 12)
	{
		CurrentTime.Month = 1;
		AdvanceYear();
	}
}

void AChronomanager::AdvanceYear()
{
	bTimeWasUpdated = true;
	CurrentTime.Year++;
}




