#pragma once

#include "CoreMinimal.h"
#include "SaveComponentData.generated.h"

USTRUCT(BlueprintType)
struct FSaveComponentData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Save & Load")
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save & Load")
	UClass* ComponentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save & Load")
	TArray<FString> RawData;
};