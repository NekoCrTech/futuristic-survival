// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IndexButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, int32, Index);

class UTextBlock;
class UButton;

UCLASS()
class FUTURISTICSURVIVAL_API UIndexButtonWithText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ExposedOnspawn), Category= "Settings")
	FText ButtonLabel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ExposedOnspawn), Category= "Settings")
	int32 Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category= "Components")
	UButton* Button;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category= "Components")
	UTextBlock* ButtonTextBlock;
	
	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClicked;
	
	UFUNCTION(BlueprintCallable)
	void SetIsSelected(bool bIsSelected);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSelected() {return bSelected;}
	
	UFUNCTION(BlueprintCallable)
	void SetIndex(const int32 InIndex) {Index = InIndex;};
	
	UFUNCTION(BlueprintNativeEvent)
	void OnSelectedStateChanged();
	
	
protected:
	UFUNCTION()
	virtual void HandleButtonClicked();
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	bool bSelected;
		
};
