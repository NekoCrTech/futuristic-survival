#pragma once

#include "CoreMinimal.h"
#include "Logger.h"
#include "SurvUtils.h"
#include "Enums/ItemQuality.h"
#include "ItemUiData.generated.h"

USTRUCT(BlueprintType)
struct FItemUIData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText	ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText	ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemQuality ItemQuality;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLinearColor ItemQualityColor;

	FItemUIData() {};

	FItemUIData(const FText& Name, const FText& Description,UTexture2D* Icon, const EItemQuality& Quality)
	{
		ItemName = Name;
		ItemDescription = Description;
		ItemIcon = Icon;
		ItemQuality = Quality;
		ItemQualityColor = GetItemQualityColor(Quality);
	}
};
