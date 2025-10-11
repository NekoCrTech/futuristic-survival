// developed by Neko


#include "SurvUtilsFunctions.h"

void USurvUtilsFunctions::AddLogMessage(const FString& Caller, const FString& Message, EErrorLevel Level)
{
	FString DisplayMessage = Caller + " - " + Message;
	Logger::GetInstance()->AddMessage(std::string(TCHAR_TO_UTF8(*DisplayMessage)),Level);
	GEngine->AddOnScreenDebugMessage(-1, 10, GetColorByErrorLevel(Level),Message);
}

float USurvUtilsFunctions::ConvertFahrenheitToCelsius(const float& Temperature)
{
	return (Temperature - 32) * 5 / 9;
}

FColor USurvUtilsFunctions::GetColorByErrorLevel(EErrorLevel Level)
{
	switch (Level)
	{
	case EErrorLevel::EL_DEBUG:
		return FColor::Silver;     // Light gray
	case EErrorLevel::EL_WARNING:
		return FColor::Yellow;
	case EErrorLevel::EL_ERROR:
		return FColor::Red;
	case EErrorLevel::EL_CRITICAL:
		return FColor(139, 0, 0);  // Dark red (custom RGB)
	default:
		return FColor::White;
	}
}
