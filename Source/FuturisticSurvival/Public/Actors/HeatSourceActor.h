// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Core/SurvActor.h"
#include "Interaction/InteractionInterface.h"
#include "NiagaraComponent.h"
#include "HeatSourceActor.generated.h"

class USphereComponent;

UCLASS()
class FUTURISTICSURVIVAL_API AHeatSourceActor : public ASurvActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	AHeatSourceActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> HeatZone;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> Emitter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* HeatFallOff;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float MaxHeatValue = 50.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float SphereRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bIsInteractableHeatSource = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText EnableText = FText::FromString("Interact");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText DisableText = FText::FromString("Interact");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bUseFuel = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsActivated = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "State", meta = (AllowPrivateAccess = "true"))
	TArray<ASurvCharacter*> ActorsInRange;
	
protected:

	virtual void BeginPlay() override;
public:
	virtual void  Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual FText GetInteractionText_Implementation() override;
	virtual void  Interact_Implementation(class ASurvCharacter* Caller) override;
	virtual bool  IsInteractable_Implementation() const override;

	virtual void UpdateFromSave_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractBP();
	
};
