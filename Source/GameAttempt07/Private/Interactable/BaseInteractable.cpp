// Copyright Big Rocket Games


#include "Interactable/BaseInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Equipment/EquipmentComponent.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseInteractable::HighlightActor_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("MIP Highlight called on: %s"), *GetName());

}

void ABaseInteractable::UnHighlightActor_Implementation()
{

}

void ABaseInteractable::InteractWithObject_Implementation(AActor* Interactor)
{
	if (!Interactor) return;

	if (UEquipmentComponent* EquipComp = Interactor->FindComponentByClass<UEquipmentComponent>())
	{
		EquipComp->EquipItem(Cast<AInteractableEquipment>(this));
	}
}

EInteractionType ABaseInteractable::GetInteractionType_Implementation() const
{
	return InteractionType;
}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

