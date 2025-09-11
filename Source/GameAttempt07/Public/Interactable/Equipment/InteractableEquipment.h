// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Interactable/BaseInteractable.h"
#include "Interactable/Equipment/EquipmentTypes.h"
#include "InteractableEquipment.generated.h"

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API AInteractableEquipment : public ABaseInteractable
{
	GENERATED_BODY()

public:

	AInteractableEquipment();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentSlot EquipmentSlot = EEquipmentSlot::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	USkeletalMeshComponent* EquipmentMesh;
};
