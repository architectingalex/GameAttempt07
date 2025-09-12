// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API UGameWidgetController : public UObject
{
	GENERATED_BODY()

	public:
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> PlayerState;
	
};
