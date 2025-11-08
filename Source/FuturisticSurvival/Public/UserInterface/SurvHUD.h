// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SurvHUD.generated.h"

class UInventoryComponent;
class UPlayerWidget;
class USurvUserWidget;
class UInventoryWidget;
struct FInventoryData;

UCLASS()
class FUTURISTICSURVIVAL_API ASurvHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASurvHUD();

	UFUNCTION(BlueprintCallable)
	void InitializeHUD();
	
	UInventoryWidget* CreateInvWidget(AActor* InOwner, const FInventoryData& InventoryData, UInventoryComponent* InventoryComponent);
	void ToggleCharacterWindow();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerInventoryCreated();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOtherInventoryCreated();
	

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Survival|HUD")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Survival|References") //TODO: convert to ReadOnly
	UPlayerWidget* PlayerWidget;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Survival|References")
	UInventoryWidget* PlayerInventoryWidget;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Survival|References")
	UInventoryWidget* OtherInventoryWidget;

	
	
};
