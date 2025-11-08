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
	FIntPoint ItemPos = FIntPoint(-1);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText	ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText	ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText UseText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bUsable = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemQuality ItemQuality = EItemQuality::Common;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLinearColor ItemQualityColor = FLinearColor::White;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 StackSize = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Weight = 0;

	FItemUIData() = default;

	FItemUIData(const FIntPoint& InvPosition, const FText& Name, const FText& Description, const FText& InUseText, const bool& Usable, UTexture2D* Icon, const EItemQuality& Quality, const int& Count, const float& InWeight)
	{
		ItemPos = InvPosition;
		ItemName = Name;
		ItemDescription = Description;
		UseText = InUseText;
		bUsable = Usable;
		ItemIcon = Icon;
		ItemQuality = Quality;
		ItemQualityColor = GetItemQualityColor(Quality);
		StackSize = Count;
		Weight = InWeight;
	}
};
