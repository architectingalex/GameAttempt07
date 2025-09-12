// Copyright Big Rocket Games


#include "UI/WidgetController/GameWidgetController.h"

void UGameWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
}

void UGameWidgetController::BroadcastInitialValues()
{
}
