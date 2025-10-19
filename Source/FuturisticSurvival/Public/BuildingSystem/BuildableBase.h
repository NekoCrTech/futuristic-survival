// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableBase.generated.h"

class UBuildableBaseDataAsset;

UCLASS()
class FUTURISTICSURVIVAL_API ABuildableBase : public AActor
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
	ABuildableBase();

	UFUNCTION()
	void SetData(const UBuildableBaseDataAsset* Data);
};
