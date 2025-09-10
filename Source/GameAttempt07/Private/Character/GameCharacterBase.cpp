// Copyright Big Rocket Games

#include "Character/GameCharacterBase.h"


AGameCharacterBase::AGameCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AGameCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
