// Copyright Big Rocket Games


#include "UI/WidgetController/OverlayWidgetController.h"
#include "ActorStats/ActorStatsComponent.h"


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

			}
		}
	}

	
}
