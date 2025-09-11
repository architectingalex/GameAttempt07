// Copyright Big Rocket Games


#include "Interactable/Equipment/InteractableEquipment.h"

AInteractableEquipment::AInteractableEquipment()
{
	EquipmentMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentMesh"));
	EquipmentMesh->SetupAttachment(RootComponent);
	
}
