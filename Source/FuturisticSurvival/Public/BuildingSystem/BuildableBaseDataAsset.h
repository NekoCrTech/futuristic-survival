// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventorySystem/Items/ItemBase.h"
#include "BuildableBaseDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UBuildableBaseDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	UStaticMesh* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	FVector2D Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	TMap<TSubclassOf<UItemBase>, int32> Cost; 
	
};
