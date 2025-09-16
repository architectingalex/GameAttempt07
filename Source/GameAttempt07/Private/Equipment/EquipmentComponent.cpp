// Copyright Big Rocket Games


#include "Equipment/EquipmentComponent.h"
#include "GameFramework/Character.h"
#include "Interactable/Equipment/InteractableEquipment.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	PrimaryInteractableEquipment.EquipmentSlot = EEquipmentSlot::Primary;
	SecondaryInteractableEquipment.EquipmentSlot = EEquipmentSlot::Secondary;
	MeleeInteractableEquipment.EquipmentSlot = EEquipmentSlot::Melee;
	ExplosiveInteractableEquipment.EquipmentSlot = EEquipmentSlot::Explosive;
	TraversalInteractableEquipment.EquipmentSlot = EEquipmentSlot::Traversal;
	ScanInteractableEquipment.EquipmentSlot = EEquipmentSlot::Scanner;
	NoneInteractableEquipment.EquipmentSlot = EEquipmentSlot::None;
	CampInteractableEquipment.EquipmentSlot = EEquipmentSlot::Camp;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEquipmentComponent::SetAttachmentMode(AInteractableEquipment* Equip, bool bAttached)
{
	if (!Equip || !Equip->SkeletalMeshComponent) return;
	USkeletalMeshComponent* Mesh = Equip->SkeletalMeshComponent;

	if (bAttached)
	{
		DisablePhysics(Mesh);
		Equip->SetActorEnableCollision(false);
	}
	else
	{
		EnablePhysics(Mesh);
		Equip->SetActorEnableCollision(true);
	}
}

void UEquipmentComponent::AttachActorToSocket(AInteractableEquipment* Equip, ACharacter* OwnerCharacter, const FName& Socket)
{
	if (!Equip || !OwnerCharacter || !OwnerCharacter->GetMesh()) return;
	if (Socket == NAME_None) return;

	Equip->AttachToComponent(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		Socket
	);
	Equip->SetActorRelativeTransform(FTransform::Identity);
}


FInteractableEquipmentStruct* UEquipmentComponent::FindSlot(EEquipmentSlot SlotType)
{
	for (FInteractableEquipmentStruct* Slot : GetAllSlots())
	{
		if (Slot->EquipmentSlot == SlotType)
		{
			return Slot;
		}
	}
	return nullptr;
}

TArray<FInteractableEquipmentStruct*> UEquipmentComponent::GetAllSlots()
{
	return {
		&PrimaryInteractableEquipment,
		&SecondaryInteractableEquipment,
		&MeleeInteractableEquipment,
		&ExplosiveInteractableEquipment,
		&TraversalInteractableEquipment,
		&ScanInteractableEquipment,
		&CampInteractableEquipment,
		&NoneInteractableEquipment
	};
}

void UEquipmentComponent::EquipItem(AInteractableEquipment* NewEquip)
{
	if (!NewEquip) return;

	EEquipmentSlot NewItemsSlot = NewEquip->InteractableEquipmentStruct.EquipmentSlot;
	if (FInteractableEquipmentStruct* Slot = FindSlot(NewItemsSlot))
	{
		if (Slot->EquipmentUsageState == EEquipmentUsageState::InUse)
		{
			ActiveSlot = Slot->EquipmentSlot;
			UnequipActiveItem();
		}

		EquipItemToSlot(NewEquip, Slot);
		SetActiveSlot(Slot->EquipmentSlot);
	}
}

void UEquipmentComponent::SetSlotFromItem(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	if (!NewEquip || !Slot) return;
	
	Slot->EquipmentName  = NewEquip->InteractableEquipmentStruct.EquipmentName;
	Slot->SkeletalMesh = NewEquip->InteractableEquipmentStruct.SkeletalMesh;
	Slot->EquippedActor = NewEquip;
	Slot->EquipmentUsageState = EEquipmentUsageState::InUse;
	Slot->HandSocket = NewEquip->InteractableEquipmentStruct.HandSocket;
	Slot->HolsterSocket = NewEquip->InteractableEquipmentStruct.HolsterSocket;
	
}

void UEquipmentComponent::EquipItemToSlot(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	if (!NewEquip || !Slot) return;

	SetSlotFromItem(NewEquip, Slot);
	SetAttachmentMode(NewEquip, true);

	// By default, just attach to holster first
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter && Slot->HolsterSocket != NAME_None)
	{
		NewEquip->AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,Slot->HolsterSocket
		);
	}

	OnEquipmentSlotChanged.Broadcast(*Slot);
}

bool UEquipmentComponent::CanAttach(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter*& OutOwner) const
{
	if (!NewEquip || !Slot)
		return false;

	OutOwner = Cast<ACharacter>(GetOwner());
	if (!OutOwner || !OutOwner->GetMesh())
	{
		return false;
	}

	if (Slot->HandSocket == NAME_None)
	{
		return false;
	}

	if (!OutOwner->GetMesh()->DoesSocketExist(Slot->HandSocket))
	{
		return false;
	}

	if (!NewEquip->SkeletalMeshComponent)
	{
		return false;
	}

	return true;
}

void UEquipmentComponent::DisablePhysics(USkeletalMeshComponent* EquipMesh)
{
	EquipMesh->SetSimulatePhysics(false);
	EquipMesh->SetEnableGravity(false);
	EquipMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	EquipMesh->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	EquipMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UEquipmentComponent::EnablePhysics(USkeletalMeshComponent* EquipMesh)
{
	EquipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EquipMesh->SetCollisionObjectType(ECC_PhysicsBody);
	EquipMesh->SetCollisionResponseToAllChannels(ECR_Block);
	EquipMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	EquipMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	EquipMesh->SetSimulatePhysics(true);
	EquipMesh->SetEnableGravity(true);
}

void UEquipmentComponent::DisableCollision(AInteractableEquipment* NewEquip)
{
	NewEquip->SetActorEnableCollision(false);
}



void UEquipmentComponent::AttachMesh(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter* OwnerCharacter)
{
	//AttachToSocket(NewEquip, OwnerCharacter, Slot);
	if (!NewEquip || !Slot || !OwnerCharacter || !OwnerCharacter->GetMesh()) return;
	NewEquip->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Slot->HandSocket);
	NewEquip->SetActorRelativeTransform(FTransform::Identity);
}

void UEquipmentComponent::AttachItemToCharacter(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	ACharacter* OwnerCharacter = nullptr;
	if (!CanAttach(NewEquip, Slot, OwnerCharacter)) return;
	SetAttachmentMode(NewEquip, true);
	AttachMesh(NewEquip, Slot, OwnerCharacter);
}

AInteractableEquipment* UEquipmentComponent::GetActiveEquipment() const
{
	switch (ActiveSlot)
	{
	case EEquipmentSlot::Primary:
		return PrimaryInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Secondary:
		return SecondaryInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Melee:
		return MeleeInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Explosive:
		return ExplosiveInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Scanner:
		return ScanInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Traversal:
		return TraversalInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::None:
		return NoneInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Camp:
		return CampInteractableEquipment.EquippedActor.Get();
	default:
		return nullptr;
	}
}

void UEquipmentComponent::AttachToSocket(EEquipmentSlot NewActiveSlot, ACharacter* OwnerCharacter, FInteractableEquipmentStruct* Slot)
{
	if (!Slot || !Slot->EquippedActor.IsValid() || !OwnerCharacter) return;
	if (Slot->EquipmentSlot == NewActiveSlot)
	{
		AttachActorToSocket(Slot->EquippedActor.Get(), OwnerCharacter, Slot->HandSocket);
	}
	else
	{
		AttachActorToSocket(Slot->EquippedActor.Get(), OwnerCharacter, Slot->HolsterSocket);
	}
}

void UEquipmentComponent::SetActiveSlot(EEquipmentSlot NewActiveSlot)
{
	if (ActiveSlot == NewActiveSlot) return;

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;
	
	for (FInteractableEquipmentStruct* Slot : GetAllSlots())
	{
		if (!Slot || !Slot->EquippedActor.IsValid()) continue;
		AttachToSocket(NewActiveSlot, OwnerCharacter, Slot);
	}
	UE_LOG(LogTemp, Error, TEXT("EquipmentComponent setting active slot to %s"),
	*UEnum::GetValueAsString(NewActiveSlot));

	ActiveSlot = NewActiveSlot;
}

void UEquipmentComponent::SetSlotToEmpty(FInteractableEquipmentStruct* Slot)
{
	Slot->EquipmentName = EEquipmentName::None;
	Slot->EquippedActor = nullptr;
	Slot->SkeletalMesh = nullptr;
	Slot->EquipmentUsageState = EEquipmentUsageState::Empty;
	Slot->HandSocket = NAME_None;
	Slot->HolsterSocket = NAME_None;
}

void UEquipmentComponent::UnequipActiveItem()
{

	AInteractableEquipment* ActiveEquipment = GetActiveEquipment();
	if (!ActiveEquipment)
	{
		return;
	}

	FInteractableEquipmentStruct* Slot = FindSlot(ActiveSlot);
	if (!Slot)
	{
		return;
	}

	if (ActiveEquipment->SkeletalMeshComponent)
	{
		USkeletalMeshComponent* EquipmentMesh = ActiveEquipment->SkeletalMeshComponent;
		EnablePhysics(EquipmentMesh);
	}
	
	ActiveEquipment->SetActorEnableCollision(true);
	ActiveEquipment->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetSlotToEmpty(Slot);
	ActiveSlot = EEquipmentSlot::None;
	OnEquipmentSlotChanged.Broadcast(*Slot);
}
