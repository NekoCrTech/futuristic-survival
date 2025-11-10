// developed by Neko

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/SurvUserWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class FUTURISTICSURVIVAL_API UPlayerHud : public USurvUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category="Components")
	class UBarXP* BarXP;
};
