// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacterBase.generated.h"

UCLASS(Abstract)
class GAMEATTEMPT07_API AGameCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGameCharacterBase();

protected:
	virtual void BeginPlay() override;
	

};
