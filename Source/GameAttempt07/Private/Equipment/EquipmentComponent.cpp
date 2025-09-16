// Copyright Big Rocket Games


#include "Equipment/EquipmentComponent.h"
#include "GameFramework/Character.h"

#include "Interactable/Equipment/InteractableEquipment.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	PrimaryInteractableEquipment.EquipmentSlot = EEquipmentSlot::Primary;
	SecondaryInteractableEquipment.EquipmentSlot = EEquipmentSlot::Secondary;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DebugPrintEquipment();
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
		// later: add melee, explosives, etc.
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

		// Always bring the new one to hand
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
	PrepareForAttachment(NewEquip);

	// By default, just attach to holster first
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter && Slot->HolsterSocket != NAME_None)
	{
		NewEquip->AttachToComponent(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			Slot->HolsterSocket
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
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter failed: invalid owner or no mesh."));
		return false;
	}

	if (Slot->HandSocket == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter: no socket specified for slot %s"),
			*UEnum::GetValueAsString(Slot->EquipmentSlot));
		return false;
	}

	if (!OutOwner->GetMesh()->DoesSocketExist(Slot->HandSocket))
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter: mesh has no socket named %s"),
			*Slot->HandSocket.ToString());
		return false;
	}

	if (!NewEquip->SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter: Equip has no SkeletalMeshComponent"));
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

void UEquipmentComponent::PrepareForAttachment(AInteractableEquipment* NewEquip)
{
	if (!NewEquip || !NewEquip->SkeletalMeshComponent) return;
	
	DisablePhysics(NewEquip->SkeletalMeshComponent);
	DisableCollision(NewEquip);
}

void UEquipmentComponent::AttachMesh(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter* OwnerCharacter)
{
	if (!NewEquip || !Slot || !OwnerCharacter || !OwnerCharacter->GetMesh()) return;

	NewEquip->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Slot->HandSocket);
	NewEquip->SetActorRelativeTransform(FTransform::Identity);
}

void UEquipmentComponent::AttachItemToCharacter(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	ACharacter* OwnerCharacter = nullptr;
	if (!CanAttach(NewEquip, Slot, OwnerCharacter)) return;

	PrepareForAttachment(NewEquip);
	AttachMesh(NewEquip, Slot, OwnerCharacter);

	UE_LOG(LogTemp, Warning, TEXT("%s attached to %s at socket %s"), *GetNameSafe(NewEquip), *OwnerCharacter->GetName(), *Slot->HandSocket.ToString());
}

AInteractableEquipment* UEquipmentComponent::GetActiveEquipment() const
{
	switch (ActiveSlot)
	{
	case EEquipmentSlot::Primary:
		return PrimaryInteractableEquipment.EquippedActor.Get();
	case EEquipmentSlot::Secondary:
		return SecondaryInteractableEquipment.EquippedActor.Get();
	default:
		return nullptr;
	}
}

void UEquipmentComponent::SetActiveSlot(EEquipmentSlot NewActiveSlot)
{
	if (ActiveSlot == NewActiveSlot) return;

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	// Step 1: holster old
	if (FInteractableEquipmentStruct* OldStruct = FindSlot(ActiveSlot))
	{
		if (OldStruct->EquippedActor.IsValid() && OldStruct->HolsterSocket != NAME_None)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: Holstering %s into %s"),
				  *OldStruct->EquippedActor->GetName(),
				  *OldStruct->HolsterSocket.ToString());

			
			OldStruct->EquippedActor->AttachToComponent(
				OwnerCharacter->GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				OldStruct->HolsterSocket
			);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: %s has no holster socket"),
				   *OldStruct->EquippedActor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: No OldStruct found for %s"),
		*UEnum::GetValueAsString(ActiveSlot));
	}

	// Step 2: if switching to None, stop here
	if (NewActiveSlot == EEquipmentSlot::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: Switching to None (empty hands)"));
		ActiveSlot = EEquipmentSlot::None;
		return;
	}

	// Step 3: attach new to hand
	if (FInteractableEquipmentStruct* NewSlot = FindSlot(NewActiveSlot))
	{
		if (NewSlot->EquippedActor.IsValid() && NewSlot->HandSocket != NAME_None)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: Attaching %s to hand socket %s"),
				   *NewSlot->EquippedActor->GetName(),
				   *NewSlot->HandSocket.ToString());
			
			NewSlot->EquippedActor->AttachToComponent(
				OwnerCharacter->GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				NewSlot->HandSocket
			);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: %s has no hand socket"),
				*NewSlot->EquippedActor->GetName());
		}
		ActiveSlot = NewActiveSlot;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetActiveSlot: No struct found for %s"),
			*UEnum::GetValueAsString(NewActiveSlot));
	}
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
	UE_LOG(LogTemp, Warning, TEXT("MIIR Called"));

	AInteractableEquipment* ActiveEquipment = GetActiveEquipment();
	if (!ActiveEquipment)
	{
		UE_LOG(LogTemp, Warning, TEXT("DropActiveEquipment: No active equipment to drop"));
		return;
	}

	FInteractableEquipmentStruct* Slot = FindSlot(ActiveSlot);
	if (!Slot)
	{
		UE_LOG(LogTemp, Warning, TEXT("DropActiveEquipment: Active slot struct not found"));
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

	UE_LOG(LogTemp, Warning, TEXT("Dropped equipment: %s"), *GetNameSafe(ActiveEquipment));

	OnEquipmentSlotChanged.Broadcast(*Slot);
}

void UEquipmentComponent::DebugPrintEquipment() const
{
	// Build list of your slots
	TArray<const FInteractableEquipmentStruct*> EquipmentSlotList = {
		&PrimaryInteractableEquipment,
		&SecondaryInteractableEquipment,
		// add the rest here: Melee, Explosive, Scanner, etc.
	};

	for (const FInteractableEquipmentStruct* Slot : EquipmentSlotList)
	{
		FString SlotName = UEnum::GetValueAsString(Slot->EquipmentSlot);

		FString MeshName = Slot->SkeletalMesh
			? Slot->SkeletalMesh->GetName()
			: TEXT("None");

		FString StateName = UEnum::GetValueAsString(Slot->EquipmentUsageState);

		FString ActorName = (Slot->EquippedActor.IsValid())
			? Slot->EquippedActor->GetName()
			: TEXT("None");

		GEngine->AddOnScreenDebugMessage(
			-1,
			0.f, // 0.f means it will refresh every tick without stacking
			FColor::Cyan,
			FString::Printf(TEXT("%s | State: %s | Mesh: %s | Actor: %s"),
				*SlotName, *StateName, *MeshName, *ActorName));
	}
}
