// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Save/SaveActorInterface.h"
#include "SurvActor.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ASurvActor : public AActor, public ISaveActorInterface
{
	GENERATED_BODY()
	
private:

	
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FGuid SaveID;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bWasSpawned = false;
	
	virtual void BeginPlay() override;

	void ChangeMeshCompVisibility(UStaticMeshComponent* MeshComp, bool Visible=false, ECollisionEnabled::Type NewCollision = ECollisionEnabled::NoCollision);

public:

	ASurvActor();
	
	virtual void Tick(float DeltaTime) override;

	virtual FGuid GetActorSaveID_Implementation();
	void SetActorGUID_Implementation(const FGuid& NewGiud);
	virtual FSaveActorData GetSaveData_Implementation();
	virtual void UpdateFromSave_Implementation();
};
