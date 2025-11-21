// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"


class UInventoryComponent;
class USurvPlaceablesMenu;
class USurvPlaceableBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingComponent();

	UFUNCTION(BlueprintCallable)
	void SelectPlaceable(TSubclassOf<USurvPlaceableBase> PlaceableClass);
	UFUNCTION(BlueprintCallable)
	void Place();
	UFUNCTION(BlueprintCallable)
	void CancelPlacement();
	UFUNCTION(BlueprintCallable)
	void RotatePlacement(const bool& bRotateRight);

	UFUNCTION(BlueprintCallable)
	void AddToUnlockedPlaceables(TArray<TSubclassOf<USurvPlaceableBase>> PlaceablesToUnlock);
	
	UFUNCTION(BlueprintCallable)
	void InitializeBuildingComponent(UInventoryComponent* InventoryComponent);

private:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "References")
	class APlaceablePreview* CurrentPreview;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "State")
	bool bInPlacementMode = false;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "State")
	TArray<TSubclassOf<USurvPlaceableBase>> UnlockedPlaceables;

	UPROPERTY()
	TSubclassOf<USurvPlaceableBase> CurrentPreviewClass;
	
	UPROPERTY()
	USurvPlaceablesMenu* PlaceablesMenuWidget;
	
	UPROPERTY()
	UInventoryComponent* Inventory;

	void SpawnPreview(TSubclassOf<USurvPlaceableBase> PlaceableClass);
};
