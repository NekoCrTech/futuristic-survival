// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemQuality.h"
#include "Structs/ItemUiData.h"
#include "Structs/SalvageItem.h"
#include "ItemBase.generated.h"

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

public:

	UFUNCTION(BlueprintCallable)
	virtual void OnUse(class ASurvCharacter* Caller) {};

	UFUNCTION(BlueprintCallable)
	float GetItemWeight() const {return ItemWeight;}
	UFUNCTION(BlueprintCallable)
	int GetStackSize() const {return MaxStackSize;}
	UFUNCTION(BlueprintCallable)
	float GetStackWeight(const int& Amount) const {return ItemWeight * Amount;}
	UFUNCTION(BlueprintCallable)
	FItemUIData GetItemUIData() const {return FItemUIData(ItemName, ItemDescription, ItemIcon, ItemQuality);}
	UFUNCTION(BlueprintCallable)
	TArray<FSalvageItem> GetSalvageData() const {return SalvageItems;}
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetPickupMesh() const {return Mesh;}
};
