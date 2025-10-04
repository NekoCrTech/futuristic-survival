// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Harvestable.generated.h"

class APickupActor;
/**
 * 
 */
class UStaticMeshComponent;

UCLASS()
class FUTURISTICSURVIVAL_API AHarvestable : public ASurvActor
{
	GENERATED_BODY()

private:
	
	AHarvestable();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HarvestableMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> RemainingHarvestableMesh;

	void SetHarvestState();
	void Harvest();
	void SpawnPickups();

	

protected:

	UPROPERTY(SaveGame)
	bool bIsHarvested = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings", meta=(AllowPrivateAccess = "true"))
	float Health = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APickupActor> PickUpActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings", meta=(AllowPrivateAccess = "true"))
	int DropSpawnQnt = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings", meta=(AllowPrivateAccess = "true"))
	FString DamageCauserTag = "DamageCauser";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings", meta=(AllowPrivateAccess = "true"))
	TArray<FTransform> SpawnPickupsTransforms;

public:
	
	virtual FSaveActorData GetSaveData_Implementation() override;
	void UpdateFromSave_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHarvestedBP();
	void OnHarvestedBP_Implementation();

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	
	
	
};
