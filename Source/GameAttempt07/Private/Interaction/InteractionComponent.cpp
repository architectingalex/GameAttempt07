// Copyright Big Rocket Games


#include "Interaction/InteractionComponent.h"
#include "Components/SphereComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	

}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractionComponent::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("MIR InteractionComponent: BeginOverlap with %s"),
	OtherActor ? *OtherActor->GetName() : TEXT("null"));

}

void UInteractionComponent::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("MIR InteractionComponent: EndOverlap with %s"),
	OtherActor ? *OtherActor->GetName() : TEXT("null"));

}


