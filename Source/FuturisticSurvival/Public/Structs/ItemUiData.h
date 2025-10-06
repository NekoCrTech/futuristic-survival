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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int ItemIdx = -1;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int StackSize = 0;

	FItemUIData() {};

	FItemUIData(const int& Index, const FText& Name, const FText& Description,UTexture2D* Icon, const EItemQuality& Quality, const int& Count)
	{
		ItemIdx = Index;
		ItemName = Name;
		ItemDescription = Description;
		ItemIcon = Icon;
		ItemQuality = Quality;
		ItemQualityColor = GetItemQualityColor(Quality);
		StackSize = Count;
	}
};
