// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/RandomizedVector.h"
#include "GameFramework/Actor.h"
#include "RandomizedMaterialActor.generated.h"

USTRUCT(BlueprintType)
struct FMaterialArray
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UMaterialInstance*> Materials;
		
};

UCLASS()
class FUTURISTICSURVIVAL_API ARandomizedMaterialActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomizedMaterialActor();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FMaterialArray> RandomizedMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ERandomizedVector RandomizationVector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bRandomize = false;
};
