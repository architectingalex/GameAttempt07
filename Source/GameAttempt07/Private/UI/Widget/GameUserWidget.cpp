// Copyright Big Rocket Games


#include "UI/Widget/GameUserWidget.h"

#include "Interactable/InteractableStructs.h"

void UGameUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();

	
}


void UGameUserWidget::HandleSlotClicked(FInteractableEquipmentStruct SlotData)
{
	OnSlotClicked.Broadcast(SlotData);
	
}

