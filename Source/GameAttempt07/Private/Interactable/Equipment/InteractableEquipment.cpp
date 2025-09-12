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
