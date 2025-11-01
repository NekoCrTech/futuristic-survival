// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvProjectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class FUTURISTICSURVIVAL_API ASurvProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASurvProjectile();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Survival|Damage", meta=(ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{10.f};

	UFUNCTION(BlueprintImplementableEvent)
	void OnImpact();
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"),  Category = "Survival|Components" )
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"),  Category = "Survival|Damage" )
	TSubclassOf<UGameplayEffect> DamageEffect;
	
};
