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

void UEquipmentComponent::TryEquip(AInteractableEquipment* NewEquip)
{
	if (!NewEquip) return;

	EEquipmentSlot NewItemsSlot = NewEquip->InteractableEquipmentStruct.EquipmentSlot;
	if (FInteractableEquipmentStruct* Slot = FindSlot(NewItemsSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found matching slot: %s"),
			*UEnum::GetValueAsString(NewItemsSlot));
		AssignToSlot(NewEquip, Slot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching slot for %s"),
			*UEnum::GetValueAsString(NewItemsSlot));
	}
}

void UEquipmentComponent::AssignToSlot(class AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	if (!NewEquip || !Slot) return;
	if (Slot->EquipmentUsageState != EEquipmentUsageState::Empty)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot %s already occupied, ignoring %s"), *UEnum::GetValueAsString(Slot->EquipmentSlot), *GetNameSafe(NewEquip));
		return;
	}

	Slot->SkeletalMesh = NewEquip->InteractableEquipmentStruct.SkeletalMesh;
	Slot->EquippedActor = NewEquip;
	Slot->EquipmentUsageState = EEquipmentUsageState::InUse;
	Slot->AttachSocket = NewEquip->InteractableEquipmentStruct.AttachSocket;


	UE_LOG(LogTemp, Warning, TEXT("Equipped %s into slot %s"), *GetNameSafe(NewEquip), *UEnum::GetValueAsString(Slot->EquipmentSlot));
	AttachToCharacter(NewEquip, Slot);
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

	if (Slot->AttachSocket == NAME_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter: no socket specified for slot %s"),
			*UEnum::GetValueAsString(Slot->EquipmentSlot));
		return false;
	}

	if (!OutOwner->GetMesh()->DoesSocketExist(Slot->AttachSocket))
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachToCharacter: mesh has no socket named %s"),
			*Slot->AttachSocket.ToString());
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

void UEquipmentComponent::AttachMeshToCharacter(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot, ACharacter* OwnerCharacter)
{
	if (!NewEquip || !Slot || !OwnerCharacter || !OwnerCharacter->GetMesh()) return;

	NewEquip->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Slot->AttachSocket);
	NewEquip->SetActorRelativeTransform(FTransform::Identity);
}

void UEquipmentComponent::AttachToCharacter(AInteractableEquipment* NewEquip, FInteractableEquipmentStruct* Slot)
{
	ACharacter* OwnerCharacter = nullptr;
	if (!CanAttach(NewEquip, Slot, OwnerCharacter)) return;

	PrepareForAttachment(NewEquip);
	AttachMeshToCharacter(NewEquip, Slot, OwnerCharacter);
	SetActiveSlot(Slot->EquipmentSlot);

	UE_LOG(LogTemp, Warning, TEXT("%s attached to %s at socket %s"), *GetNameSafe(NewEquip), *OwnerCharacter->GetName(), *Slot->AttachSocket.ToString());
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
	ActiveSlot = NewActiveSlot;
}

void UEquipmentComponent::DropActiveEquipment()
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

	Slot->EquippedActor = nullptr;
	Slot->SkeletalMesh = nullptr;
	Slot->EquipmentUsageState = EEquipmentUsageState::Empty;
	Slot->AttachSocket = NAME_None;

	ActiveSlot = EEquipmentSlot::None;

	UE_LOG(LogTemp, Warning, TEXT("Dropped equipment: %s"), *GetNameSafe(ActiveEquipment));
	
}
