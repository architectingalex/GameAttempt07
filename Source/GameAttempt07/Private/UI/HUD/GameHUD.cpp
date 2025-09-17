// Copyright Big Rocket Games


#include "UI/HUD/GameHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AGameHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}
		return OverlayWidgetController;
}

void AGameHUD::InitOverlay(AGamePlayerController* PC)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialised, please fill out BP_GameHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialised, please fill out BP_GameHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UGameUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	Widget->AddToViewport();
	WidgetController->BroadcastInitialValues();
}

void AGameHUD::ToggleEquipmentMenu(bool bShow)
{
	if (OverlayWidget)
	{
		if (!EquipmentMenuWidget) // cache it
		{
			EquipmentMenuWidget = Cast<UGameUserWidget>(OverlayWidget->GetWidgetFromName(TEXT("EquipmentMenu")));

			if (EquipmentMenuWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("EquipmentMenuWidget cached: %s"), *EquipmentMenuWidget->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not find EquipmentMenu in Overlay!"));
				return;
			}
		}

		EquipmentMenuWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("ToggleEquipmentMenu: EquipmentMenu set %s"),
			bShow ? TEXT("Visible") : TEXT("Hidden"));
	}
}



