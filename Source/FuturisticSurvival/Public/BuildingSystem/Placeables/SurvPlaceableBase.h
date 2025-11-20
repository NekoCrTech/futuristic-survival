// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "PlaceableCategoryEnum.h"
#include "UObject/Object.h"
#include "SurvPlaceableBase.generated.h"


class APlaceableActor;
class UItemBase;

UCLASS(Blueprintable)
class FUTURISTICSURVIVAL_API USurvPlaceableBase : public UObject
{
	GENERATED_BODY()
protected:
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Stats")
	EPlaceableCategory Category;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "World Data")
	TSubclassOf<APlaceableActor> Buildable;

public:
	UFUNCTION(BlueprintCallable)
	void Use(AActor* Instigator);
	
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetPlaceableMesh() const {return Mesh;}
	
	UFUNCTION(BlueprintCallable)
	TSubclassOf<APlaceableActor> GetPlaceableClass() {return Buildable; }
	
	UFUNCTION(BlueprintCallable)
	EPlaceableCategory GetCategory() const {return Category; }
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const {return Icon; }
	
};
