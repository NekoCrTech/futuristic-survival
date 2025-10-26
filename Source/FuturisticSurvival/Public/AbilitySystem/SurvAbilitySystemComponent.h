// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SurvAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FUTURISTICSURVIVAL_API USurvAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	USurvAbilitySystemComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	virtual void BeginPlay() override;
};
