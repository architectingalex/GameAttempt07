// Copyright Big Rocket Games


#include "Interactable/BaseInteractable.h"
#include "Components/StaticMeshComponent.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(Mesh);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->InitSphereRadius(100.f);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void ABaseInteractable::HighlightActor_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("MIP Highlight called on: %s"), *GetName());

}

void ABaseInteractable::UnHighlightActor_Implementation()
{

}

void ABaseInteractable::InteractWithObject_Implementation(AActor* Interactor)
{
	Destroy();
}

EInteractionType ABaseInteractable::GetInteractionType_Implementation() const
{
	return InteractionType;
}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

