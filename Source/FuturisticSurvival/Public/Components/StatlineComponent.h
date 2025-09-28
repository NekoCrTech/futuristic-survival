// Developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/StatEnum.h"
#include "Structs/Stat.h"
#include "StatlineComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UStatlineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatlineComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const EStat Stat) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FStat Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FStat Stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FStat Energy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FStat Thirst = FStat(100,100,-0.25);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FStat Hunger = FStat(100,100,-0.125);
		
	void TickStats(const float& DeltaTime);
		
};
