// Copyright Big Rocket Games


#include "Character/GameCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Interaction/InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGameCharacter::AGameCharacter()
{

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->InitSphereRadius(125.f);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionSphere->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	InteractionSphere->SetupAttachment(RootComponent);

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(InteractionComponent, &UInteractionComponent::OnInteractionBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(InteractionComponent, &UInteractionComponent::OnInteractionEndOverlap);


}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}


