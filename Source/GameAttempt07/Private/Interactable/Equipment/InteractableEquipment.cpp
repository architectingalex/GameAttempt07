// Copyright Big Rocket Games


#include "Interactable/Equipment/InteractableEquipment.h"

void AInteractableEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

AInteractableEquipment::AInteractableEquipment()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentMesh"));
	RootComponent = SkeletalMeshComponent;

	EnablePhysics();
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(SkeletalMeshComponent);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->InitSphereRadius(100.f);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	
	// Fill out the struct so EquipComponent can copy it
	InteractableEquipmentStruct.SkeletalMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();
	InteractableEquipmentStruct.AttachSocket = TEXT("WeaponSocket"); // or whatever makes sense
	InteractableEquipmentStruct.EquipmentSlot = EEquipmentSlot::Primary;
	InteractableEquipmentStruct.EquipmentUsageState = EEquipmentUsageState::Empty;
}

void AInteractableEquipment::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (InteractableEquipmentStruct.SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(InteractableEquipmentStruct.SkeletalMesh);
	}
}

void AInteractableEquipment::EnablePhysics()
{
	SkeletalMeshComponent->SetSimulatePhysics(true);
	SkeletalMeshComponent->SetEnableGravity(true);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SkeletalMeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
}
