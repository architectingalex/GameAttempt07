// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/GameUserWidget.h"
#include "GameHUD.generated.h"
struct FWidgetControllerParams;
class UOverlayWidgetController;


/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	TObjectPtr<UGameUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS);

	
protected:
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
