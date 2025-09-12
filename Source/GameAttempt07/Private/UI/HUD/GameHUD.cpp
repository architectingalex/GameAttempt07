// Copyright Big Rocket Games


#include "UI/HUD/GameHUD.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
	
}
