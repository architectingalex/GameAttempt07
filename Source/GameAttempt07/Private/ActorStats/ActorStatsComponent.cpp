// Copyright Big Rocket Games


#include "ActorStats/ActorStatsComponent.h"

UActorStatsComponent::UActorStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UActorStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UActorStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

