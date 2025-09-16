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
				OnHealthChanged.Broadcast(Stats->CurrentHealth);
				OnMaxHealthChanged.Broadcast(Stats->MaxHealth);

			}
			if (UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>())
			{
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Primary, EquipmentComponent->PrimaryInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Secondary, EquipmentComponent->SecondaryInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Melee, EquipmentComponent->MeleeInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Explosive, EquipmentComponent->ExplosiveInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Traversal, EquipmentComponent->TraversalInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Scanner, EquipmentComponent->ScanInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::Camp, EquipmentComponent->CampInteractableEquipment);
				OnEquipmentChanged.Broadcast(EEquipmentSlot::None, EquipmentComponent->NoneInteractableEquipment);
				
				EquipmentComponent->OnEquipmentSlotChanged.AddDynamic(this, &UOverlayWidgetController::HandleEquipmentSlotChanged);
			}
		}
	}
}

void UOverlayWidgetController::HandleSlotClicked(FInteractableEquipmentStruct SlotData)
{

	UE_LOG(LogTemp, Error, TEXT("OverlayWidgetController got click for slot %s"),
	*UEnum::GetValueAsString(SlotData.EquipmentSlot));
	
	if (APlayerController* PC = Cast<APlayerController>(PlayerController))
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>())
			{
				EquipmentComponent->SetActiveSlot(SlotData.EquipmentSlot);
			}
		}
	}
}

void UOverlayWidgetController::HandleEquipmentSlotChanged(FInteractableEquipmentStruct NewSlotInfo)
{
	OnEquipmentChanged.Broadcast(NewSlotInfo.EquipmentSlot, NewSlotInfo);
}
