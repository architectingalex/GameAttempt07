// Copyright Big Rocket Games

#include "UI/Widget/EquipmentSlotWidget.h"

#include "UI/WidgetController/OverlayWidgetController.h"

void UEquipmentSlotWidget::SetWidgetController(UObject* InWidgetController)
{
	Super::SetWidgetController(InWidgetController);

	if (UOverlayWidgetController* Controller = Cast<UOverlayWidgetController>(InWidgetController))
	{
		Controller->OnEquipmentChanged.AddDynamic(this, &UEquipmentSlotWidget::HandleEquipmentChanged);
		UE_LOG(LogTemp, Error, TEXT("Slot widget %s bound to controller"), *GetName());

		// Bind this slot’s click back to controller
		OnSlotClicked.AddDynamic(Controller, &UOverlayWidgetController::HandleSlotClicked);

		UE_LOG(LogTemp, Error, TEXT("%s bound to controller"), *GetName());
	}
}

void UEquipmentSlotWidget::HandleEquipmentChanged(EEquipmentSlot ChangedSlot, FInteractableEquipmentStruct NewSlotInfo)
{
	if (ChangedSlot == SlotType)
	{
		CurrentSlotData = NewSlotInfo;

		// TODO: update visuals here (icon, mesh name, etc.)
		UE_LOG(LogTemp, Error, TEXT("Slot %s got update for slot %d"), *GetName(), (int)ChangedSlot);
	}
}

void UEquipmentSlotWidget::HandleButtonClicked()
{
	UE_LOG(LogTemp, Error, TEXT("Button clicked in %s, broadcasting struct %s"), 
	*GetName(),
	*UEnum::GetValueAsString(CurrentSlotData.EquipmentSlot));
	OnSlotClicked.Broadcast(CurrentSlotData);
}
