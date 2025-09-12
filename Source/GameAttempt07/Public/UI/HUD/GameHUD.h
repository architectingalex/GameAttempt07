// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/GameUserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API AGameHUD : public AHUD
{
	GENERATED_BODY()

	public:

	TObjectPtr<UGameUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameUserWidget> OverlayWidgetClass;
	
};
