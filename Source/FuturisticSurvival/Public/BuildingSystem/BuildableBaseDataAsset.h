// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/BuildingPartType.h"
#include "Structs/AttachmentPointData.h"
#include "InventorySystem/Items/ItemBase.h"
#include "BuildableBaseDataAsset.generated.h"

class ABuildableBase;
/**
 * 
 */
UCLASS(BlueprintType)
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	TSubclassOf<ABuildableBase> Buildable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	TArray<FAttachmentPointData> AttachmentPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	EBuildingPartType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	FVector2D Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	TMap<TSubclassOf<UItemBase>, int32> Cost;

public:
	UStaticMesh* GetBuildingMesh() const {return Mesh;}
	TSubclassOf<ABuildableBase> GetBuildable() {return Buildable;}
	TArray<FAttachmentPointData> GetAttachments() const {return AttachmentPoints;}
	EBuildingPartType GetType() const {return Type;}
};
