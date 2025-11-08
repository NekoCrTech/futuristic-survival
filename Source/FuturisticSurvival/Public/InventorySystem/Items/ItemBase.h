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
	FText ItemUseText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	bool bUsable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	FText PickupText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	EItemQuality ItemQuality;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	int32 MaxStackSize = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", Meta = (AllowPrivateAccess = "true"))
	int32 CurrentStackSize = 1;
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
	int32 GetStackSize() const {return MaxStackSize;}
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentStack() const {return CurrentStackSize;}
	UFUNCTION(BlueprintCallable)
	float GetStackWeight() const {return ItemWeight * CurrentStackSize;}
	UFUNCTION(BlueprintCallable)
	FItemUIData GetItemUIData(const FIntPoint& ItemPos) const {return FItemUIData(ItemPos, ItemName, ItemDescription,ItemUseText,bUsable, ItemIcon, ItemQuality, CurrentStackSize, ItemWeight);}
	UFUNCTION(BlueprintCallable)
	TArray<FSalvageItem> GetSalvageData() const {return SalvageItems;}
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetPickupMesh() const {return Mesh;}
	UFUNCTION(BlueprintCallable)
	FText GetPickupText() const {return PickupText;}
	
};
