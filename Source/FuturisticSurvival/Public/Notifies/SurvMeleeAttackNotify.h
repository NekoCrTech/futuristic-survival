// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SurvMeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API USurvMeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = "Survival|Debugs")
	bool bDebug = true;

	UPROPERTY(EditAnywhere, Category = "Survival|Socket")
	FName SocketName{"FX_Trail_01_R"};

	UPROPERTY(EditAnywhere, Category = "Survival|Socket")
	float SocketExtensionOffset = 40.f;
	UPROPERTY(EditAnywhere, Category = "Survival|Socket")
	float SphereTraceRadius = 60.f;

	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;

	void SendEventToActors(const TArray<FHitResult>& Hits, USkeletalMeshComponent* MeshComp) const;
};

