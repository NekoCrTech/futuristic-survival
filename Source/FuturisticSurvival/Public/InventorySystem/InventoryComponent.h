// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Save/SaveActorInterface.h"
#include "Structs/ItemUiData.h"
#include "InventoryComponent.generated.h"

class UItemBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUTURISTICSURVIVAL_API UInventoryComponent : public UActorComponent, public ISaveActorInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	float MaxWeight = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true"))
	float CurrentWeight = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "InventoryData", Meta = (AllowPrivateAccess = "true")) //TODO: make it EditDefaultOnly
	TArray<TSubclassOf<UItemBase>> InventoryContents;

	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	bool IsOverCarryWeight(const float& ItemWeight) const;

protected:
	virtual void BeginPlay() override;

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	bool AddItemToTop(TSubclassOf<UItemBase> Item);

	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	bool AddItemAtIndex(TSubclassOf<UItemBase> Item, int& Index);

	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	bool AddItemToStackAtIndex(TSubclassOf<UItemBase> Item, const int& Index);

	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	TArray<FItemUIData> GetInventoryUIData() const;
};
