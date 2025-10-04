// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Structs/SaveActorData.h"
#include "Structs/SaveComponentData.h"
#include "UObject/Interface.h"
#include "SaveActorInterface.generated.h"





// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveActorInterface : public UInterface
{
	GENERATED_BODY()
};


class FUTURISTICSURVIVAL_API ISaveActorInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	FGuid GetActorSaveID();
	virtual FGuid GetActorSaveID_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	void SetActorGUID(const FGuid& NewGiud);
	virtual void SetActorGUID_Implementation(const FGuid& NewGiud);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	FSaveActorData GetSaveData();
	virtual FSaveActorData GetSaveData_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	void UpdateFromSave();
	virtual void UpdateFromSave_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	FSaveComponentData GetSaveComponentData();
	virtual FSaveComponentData GetSaveComponentData_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save & Load")
	void SetSaveComponentData(FSaveComponentData Data);
	virtual void SetSaveComponentData_Implementation(FSaveComponentData Data);
};
