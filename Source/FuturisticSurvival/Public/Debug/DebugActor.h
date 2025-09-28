// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugActor.generated.h"

UCLASS()
class FUTURISTICSURVIVAL_API ADebugActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADebugActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	bool GetDebugEnabled() const {return bDebugEnabled;}
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void SetDebugEnabled(bool bEnabled) {bDebugEnabled = bEnabled;}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	bool bDebugEnabled = true;
	
	

};
