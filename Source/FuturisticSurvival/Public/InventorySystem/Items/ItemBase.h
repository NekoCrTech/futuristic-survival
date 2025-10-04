// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Shoddy      UMETA(DisplayName = "Shoddy"),
	Common      UMETA(DisplayName = "Common"),
	Quality     UMETA(DisplayName = "Quality"),
	Masterwork  UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};

USTRUCT(BlueprintType)
struct FSalvageItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Tag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UJunkItemBase> Item;
};

UCLASS(Blueprintable)
class FUTURISTICSURVIVAL_API UItemBase : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	FText ItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	EItemQuality ItemQuality;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	int MaxStackSize = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	TArray<FSalvageItem> SalvageItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float ItemWeight = 1.0f;
	
};
