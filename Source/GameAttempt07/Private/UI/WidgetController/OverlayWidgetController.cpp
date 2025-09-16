// Copyright Big Rocket Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "ActorStats/ActorStatsComponent.h"
#include "Equipment/EquipmentComponent.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	if (!PlayerController) return;
	if (APlayerController* PC = Cast<APlayerController>(PlayerController))
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (UActorStatsComponent* Stats = Pawn->FindComponentByClass<UActorStatsComponent>())
			{
				// Fire delegates with current values
				OnHealthChanged.Broadcast(Stats->CurrentHealth);
				OnMaxHealthChanged.Broadcast(Stats->MaxHealth);
				UE_LOG(LogTemp, Error, TEXT("SOS_stage 5"));

			}
			if (UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>())
			{
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Primary, EquipmentComponent->PrimaryInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Secondary, EquipmentComponent->SecondaryInteractableEquipment);
				
				EquipmentComponent->OnEquipmentSlotChanged.AddDynamic(this, &UOverlayWidgetController::HandleEquipmentSlotChanged);
			}
		}
	
	}
	
}

void UOverlayWidgetController::HandleEquipmentSlotChanged(FInteractableEquipmentStruct NewSlotInfo)
{
	OnEquipmentChanged.Broadcast(NewSlotInfo.EquipmentSlot, NewSlotInfo);
}
