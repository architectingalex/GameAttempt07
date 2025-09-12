// Copyright Big Rocket Games


#include "ActorStats/ActorStatsComponent.h"

UActorStatsComponent::UActorStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UActorStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;
	
}

void UActorStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

