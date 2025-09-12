// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Interactable/BaseInteractable.h"
#include "Interactable/InteractableStructs.h"
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
	void BeginPlay();
	void EnablePhysics();
	AInteractableEquipment();
	void OnConstruction(const FTransform& Transform);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentName EquipmentName = EEquipmentName::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FInteractableEquipmentStruct InteractableEquipmentStruct;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Equipment")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	EEquipmentSlot GetSlot() const { return InteractableEquipmentStruct.EquipmentSlot;}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment|Data")
	UDataTable* EquipmentDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment|Data")
	FName DataRowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* CollisionSphere;



};
