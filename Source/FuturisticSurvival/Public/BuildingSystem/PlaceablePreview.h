// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/BuildingPartType.h"
#include "GameFramework/Actor.h"
#include "PlaceablePreview.generated.h"

class USurvPlaceableBase;
class USphereComponent;
class UBuildableBaseDataAsset;

UCLASS()
class FUTURISTICSURVIVAL_API APlaceablePreview : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PreviewMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildablePreview", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* GoodMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildablePreview", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* BadMaterial;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess= "true"),Category = "State")
	bool bCanBeBuilt = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess= "true"),Category = "State")
	bool bSnapped = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess= "true"),Category = "State")
	bool bRotated = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess= "true"),Category = "State")
	EBuildingPartType PartType;

	void UpdateMaterial();

protected:
	
	virtual void BeginPlay() override;

public:	
	APlaceablePreview();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetPreview(TSubclassOf<USurvPlaceableBase> PlaceableClass);
	void SnapPreviewToLocation(const FVector& TargetLocation);

	bool IsRotated() const {return bRotated;}
	void SetIsRotated(const bool& bInRotated){bRotated = bInRotated;}

	EBuildingPartType GetPartType() const{return PartType;}
	void SetPartType(const EBuildingPartType& Type){PartType = Type;}
};


// TODO: Check on tick if is buildable or not. If current 