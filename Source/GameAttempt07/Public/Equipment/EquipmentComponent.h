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
	void AttachToSocket(EEquipmentSlot NewActiveSlot, ACharacter* OwnerCharacter, FInteractableEquipmentStruct* Slot);

	/** State control */
	void SetActiveSlot(EEquipmentSlot NewActiveSlot);
	void SetSlotToEmpty(FInteractableEquipmentStruct* Slot);

	/** Debug */


	UPROPERTY(BlueprintAssignable, Category="Equipment")
	FOnEquipmentSlotChanged OnEquipmentSlotChanged;

	/** Slots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct PrimaryInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct SecondaryInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct MeleeInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct ExplosiveInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct CampInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct TraversalInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct NoneInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct ScanInteractableEquipment;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetAttachmentMode(AInteractableEquipment* Equip, bool bAttached);
	void AttachActorToSocket(AInteractableEquipment* Equip, ACharacter* OwnerCharacter, const FName& Socket);


private:
	/** Equip helpers */	
	void EquipItemToSlot(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);
	void SetSlotFromItem(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	/** Attachment helpers */
	bool CanAttach(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OutOwner) const;
	//bool PrepareForAttachement(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OwnerCharacter);
	
	void AttachMesh(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter* OwnerCharacter);
	void AttachItemToCharacter(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	/** Physics / collision helpers */
	void DisablePhysics(USkeletalMeshComponent* EquipMesh);
	void EnablePhysics(USkeletalMeshComponent* EquipMesh);
	void DisableCollision(AInteractableEquipment* NewEquip);

	/** Internal data */
	TArray<FInteractableEquipmentStruct*> GetAllSlots();
	EEquipmentSlot ActiveSlot = EEquipmentSlot::None;

};
