// developed by Neko


#include "SurvUtils.h"

TArray<FString> ChopString(FString Source, char split)
{
	TArray<FString> Ret;
	FString LSide, RSide;

	while (Source.Split(&split, &LSide, &RSide))
	{
		Ret.Add(LSide);
		Source = RSide;
		LSide.Empty();
	}
	if (RSide.IsEmpty())
	{
		Ret.Add(RSide);
	}
	return Ret;
}

FLinearColor GetItemQualityColor(const EItemQuality& ItemQuality)
{
	switch (ItemQuality)
	{
	case EItemQuality::Shoddy:
		return FLinearColor(0.5f, 0.5f, 0.5f); // dull gray

	case EItemQuality::Common:
		return FLinearColor::White; // plain white

	case EItemQuality::Quality:
		return FLinearColor(0.0f, 0.6f, 0.0f); // green

	case EItemQuality::Masterwork:
		return FLinearColor(0.25f, 0.4f, 1.0f); // blue

	case EItemQuality::Grandmaster:
		return FLinearColor(0.7f, 0.2f, 0.9f); // purple

	default:
		return FLinearColor::Black; // fallback / error case
	}
}

