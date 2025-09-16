#pragma once

#include "CoreMinimal.h"
#include "Interactable/Equipment/EquipmentEnums.h"
#include "Interactable/Equipment/EquipmentTypes.h"
#include "InteractableStructs.generated.h"

class USkeletalMesh;
class UTexture2D;
class AActor;
class AInteractableEquipment;


USTRUCT(BlueprintType)
struct GAMEATTEMPT07_API FInteractableEquipmentStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentName EquipmentName = EEquipmentName::Pistol;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentSlot EquipmentSlot = EEquipmentSlot::Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentUsageState EquipmentUsageState = EEquipmentUsageState::Empty;

	UPROPERTY()
	TWeakObjectPtr<AInteractableEquipment> EquippedActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FName AttachSocket = NAME_None;


};