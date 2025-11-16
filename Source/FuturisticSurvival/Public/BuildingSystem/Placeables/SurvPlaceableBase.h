// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SurvPlaceableBase.generated.h"


class UItemBase;

UCLASS(Blueprintable)
class FUTURISTICSURVIVAL_API USurvPlaceableBase : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI Data")
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	UStaticMesh* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	FVector2D Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	TMap<TSubclassOf<UItemBase>, int32> Cost;

public:
	UFUNCTION(BlueprintCallable)
	void Use(AActor* Instigator);
	
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetPlaceableMesh() const {return Mesh;}
	
};
