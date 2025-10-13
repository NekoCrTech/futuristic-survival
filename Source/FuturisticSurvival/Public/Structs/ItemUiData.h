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
	FText UseText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bUsable = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint ItemSize = FIntPoint(1, 1);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemQuality ItemQuality = EItemQuality::Common;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLinearColor ItemQualityColor = FLinearColor::White;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int StackSize = 0;

	FItemUIData() = default;

	FItemUIData(const int& Index, const FText& Name, const FText& Description, const FText& InUseText, const bool& Usable,const FIntPoint& Size, UTexture2D* Icon, const EItemQuality& Quality, const int& Count)
	{
		ItemIdx = Index;
		ItemName = Name;
		ItemDescription = Description;
		UseText = InUseText;
		bUsable = Usable;
		ItemSize = Size;
		ItemIcon = Icon;
		ItemQuality = Quality;
		ItemQualityColor = GetItemQualityColor(Quality);
		StackSize = Count;
	}
};
