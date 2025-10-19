// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Enums/BuildingPartType.h"
#include "AttachmentPoint.generated.h"


class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UAttachmentPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	UAttachmentPoint();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	USphereComponent* AttachmentSphere;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	TArray<EBuildingPartType> AcceptedToSnapParts;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AttachmentPointData", meta = (AllowPrivateAccess = "true"))
	bool bAttachmentIsActive = true;
};
