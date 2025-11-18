// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"

class UBuildableBaseDataAsset;

UCLASS()
class FUTURISTICSURVIVAL_API APlaceableActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"),Category = "Components")
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"),Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"), Category = "Data")
	TArray<AActor*> AttachedActors;

protected:
	virtual void BeginPlay() override;

public:	
	APlaceableActor();

	UFUNCTION()
	void SetPlaceableClass(TSubclassOf<USurvPlaceableBase> PlaceableClass);
};
