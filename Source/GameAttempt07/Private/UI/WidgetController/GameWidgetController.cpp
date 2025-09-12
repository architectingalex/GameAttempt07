// Copyright Big Rocket Games


#include "UI/WidgetController/GameWidgetController.h"

void UGameWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
}
