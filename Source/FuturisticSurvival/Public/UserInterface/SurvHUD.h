// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "HudInterface.h"
#include "GameFramework/HUD.h"
#include "SurvHUD.generated.h"

class UPlayerHud;
class USurvUserWidget;
class UInventoryWidget;
struct FInventoryData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHudCreated);

UCLASS()
class FUTURISTICSURVIVAL_API ASurvHUD : public AHUD, public IHudInterface
{
	GENERATED_BODY()

public:

	void InitializeHUD();
	
	void ToggleCharacterWindow(bool bUseOtherInventory = false);
	
	FOnHudCreated OnHudCreated;
	
	virtual UInventoryWidget* CreateInventoryWidget_Implementation(AActor* InOwner, const FInventoryData& InventoryData) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Survival|HUD")
	TSubclassOf<UPlayerHud> PlayerWidgetClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Survival|References") //TODO: convert to ReadOnly
	UPlayerHud* PlayerWidget;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Survival|References")
	UInventoryWidget* OtherInventoryWidget;

};
