// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Harvestable.generated.h"


/**
 * Harvestable actor is for resources than can be harvested with a tool and will not regrow like a tree
 */
class UStaticMeshComponent;
class APickupActor;

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

	UFUNCTION(BlueprintCallable)
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
	virtual void UpdateFromSave_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHarvestedBP();
	void OnHarvestedBP_Implementation();

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	
	
	
};
