// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/RandomizedVector.h"
#include "RandomizedActor.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ARandomizedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ARandomizedActor();
	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:
	
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> ActorOptions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ERandomizedVector RandomizationVector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bOverrideRandomization = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings", meta = (AllowPrivateAccess = "true"))
	int32 OverrideIndex = 0;
};
