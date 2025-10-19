// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Enums/BuildingPartType.h"
#include "GameFramework/Actor.h"
#include "AttachmentPoint.generated.h"

class USphereComponent;

UCLASS()
class FUTURISTICSURVIVAL_API AAttachmentPoint : public AActor
{
	GENERATED_BODY()

public:

	AAttachmentPoint();
	void SetAcceptedToSnapParts(const TArray<EBuildingPartType>& InAcceptedToSnapParts){AcceptedToSnapParts = InAcceptedToSnapParts;}
	void SetOwnerActor(AActor* InActor){AttachmentOwner = InActor;}
	void SetOwnerType(const EBuildingPartType& BuildingPartType){OwnerBuildingType = BuildingPartType;}
	bool GetRotateMesh() const {return bRotateMesh;}
	void SetRotateMesh(const bool& bRotate) {bRotateMesh = bRotate;}
	bool GetIsActiveAttachment() const {return bAttachmentIsActive;}
	void SetIsActiveAttachment(const bool& bActive) {bAttachmentIsActive = bActive;}

	TArray<EBuildingPartType> GetAcceptedParts() const {return AcceptedToSnapParts;}
	AActor* GetAttachmentOwner() const {return AttachmentOwner;}

	UFUNCTION()
	void OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	USphereComponent* AttachmentSphere;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	TArray<EBuildingPartType> AcceptedToSnapParts;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	bool bAttachmentIsActive = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	bool bRotateMesh = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	AActor* AttachmentOwner;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	EBuildingPartType OwnerBuildingType;
	
};
