// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingSystem/BuildableBaseDataAsset.h"
#include "BuildingComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool SelectBuilding(UBuildableBaseDataAsset* Data);
	UFUNCTION(BlueprintCallable)
	void PlaceBuilding();
	UFUNCTION(BlueprintCallable)
	void CancelPlacement();
	UFUNCTION(BlueprintCallable)
	void RotateBuilding(const bool& bRotateRight);

	UFUNCTION(BlueprintCallable)
	void AddToUnlockedBuildings(TArray<UBuildableBaseDataAsset*> BuildingsToUnlock);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "References")
	APlayerController* PlayerController;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "References")
	class ASurvPlayerCharacter* Owner;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "References")
	class ABuildablePreview* CurrentPreview;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "References")
	TSubclassOf<ABuildablePreview> PreviewClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "State")
	bool bInPlacementMode = false;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "State")
	TArray<UBuildableBaseDataAsset*> UnlockedBuildings;

	UPROPERTY()
	UBuildableBaseDataAsset* CurrentPreviewData;

	void SpawnPreview(UBuildableBaseDataAsset* Data);
	
};
