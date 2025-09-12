// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable/Equipment/InteractableEquipment.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEATTEMPT07_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();
	void AssignToSlot(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);
	void DebugPrintEquipment() const;
	bool CanAttach(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OutOwner) const;
	void DisablePhysics(USkeletalMeshComponent* EquipMesh);
	void EnablePhysics(USkeletalMeshComponent* EquipMesh);
	void DisableCollision(AInteractableEquipment* NewEquip);
	void PrepareForAttachment(AInteractableEquipment* NewEquip);
	bool PrepareForAttachement(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OwnerCharacter);
	void AttachMeshToComponent(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	void DropActiveEquipment();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FInteractableEquipmentStruct* FindSlot(EEquipmentSlot SlotType);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct PrimaryInteractableEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	FInteractableEquipmentStruct SecondaryInteractableEquipment;


	
	void TryEquip(class AInteractableEquipment* NewEquip);
	void AttachMeshToCharacter(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot,
	                           ACharacter* OwnerCharacter);
	void AttachToCharacter(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot);

	AInteractableEquipment* GetActiveEquipment() const;
	void SetActiveSlot(EEquipmentSlot NewActiveSlot);

private:
	TArray<FInteractableEquipmentStruct*> GetAllSlots();

	EEquipmentSlot ActiveSlot = EEquipmentSlot::None;
	
protected:
	virtual void BeginPlay() override;
	
	

};
