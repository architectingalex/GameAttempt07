// Copyright Big Rocket Games


#include "Interactable/BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseInteractable::HighlightActor()
{
}

void ABaseInteractable::UnHighlightActor()
{
}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

