// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable/Equipment/InteractableEquipment.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentSlotChanged, FInteractableEquipmentStruct, NewSlotInfo);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEATTEMPT07_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEquipmentComponent();

	/** High-level operations */
	void EquipItem(class AInteractableEquipment* NewEquip);
	void UnequipActiveItem();

	/** Queries */
	FInteractableEquipmentStruct* FindSlot(EEquipmentSlot SlotType);
	AInteractableEquipment* GetActiveEquipment() const;

	/** State control */
	void SetActiveSlot(EEquipmentSlot NewActiveSlot);

	/** Debug */
	void DebugPrintEquipment() const;

	UPROPERTY(BlueprintAssignable, Category="Equipment")
	FOnEquipmentSlotChanged OnEquipmentSlotChanged;

	/** Slots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct PrimaryInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct SecondaryInteractableEquipment;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Equip helpers */	
	void EquipItemToSlot(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);
	void SetSlotFromItem(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	/** Attachment helpers */
	bool CanAttach(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OutOwner) const;
	//bool PrepareForAttachement(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OwnerCharacter);
	void PrepareForAttachment(AInteractableEquipment* NewEquip);
	void AttachMesh(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter* OwnerCharacter);
	void AttachItemToCharacter(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	/** Physics / collision helpers */
	void DisablePhysics(USkeletalMeshComponent* EquipMesh);
	void EnablePhysics(USkeletalMeshComponent* EquipMesh);
	void DisableCollision(AInteractableEquipment* NewEquip);

	/** Internal data */
	TArray<FInteractableEquipmentStruct*> GetAllSlots();
	EEquipmentSlot ActiveSlot = EEquipmentSlot::None;


	

	

	
	

	

	
	
	
	





	

private:

	

	
	

};
