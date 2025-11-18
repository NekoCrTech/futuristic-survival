// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlaceableButtonWidget.generated.h"

class UImage;
class UButton;
class USurvPlaceableBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlaceableButtonClicked, TSubclassOf<USurvPlaceableBase>, PlaceableClass);
UCLASS()
class FUTURISTICSURVIVAL_API UPlaceableButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UButton* Button;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget), Category="Components")
	UImage* PlaceableIcon;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlaceableButtonClicked OnPlaceableButtonClicked;
	
	UFUNCTION(BlueprintCallable)
	void SetPlaceableClass(TSubclassOf<USurvPlaceableBase> InPlaceableClass);
	
	UFUNCTION()
	void HandleButtonClicked();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	TSubclassOf<USurvPlaceableBase> PlaceableClass;
	
};
