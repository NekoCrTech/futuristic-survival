// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Save/SaveActorInterface.h"
#include "Structs/SaveActorData.h"
#include "Logger.h"
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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, SaveGame)
	bool bWasSpawned = false;
	
	virtual void BeginPlay() override;

	void ChangeMeshCompVisibility(UStaticMeshComponent* MeshComp, bool Visible=false, ECollisionEnabled::Type NewCollision = ECollisionEnabled::NoCollision);

public:

	ASurvActor();
	
	virtual void Tick(float DeltaTime) override;

	virtual FGuid GetActorSaveID_Implementation() override;
	void SetActorGUID_Implementation(const FGuid& NewGiud) override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void UpdateFromSave_Implementation() override;

	void SetWasSpawned(const bool& IsSpawned);
};
