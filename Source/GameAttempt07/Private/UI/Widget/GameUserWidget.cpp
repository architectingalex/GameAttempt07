// Copyright Big Rocket Games


#include "UI/Widget/GameUserWidget.h"

void UGameUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
	UE_LOG(LogTemp, Error, TEXT("SOS_stage 4"));
	
}

