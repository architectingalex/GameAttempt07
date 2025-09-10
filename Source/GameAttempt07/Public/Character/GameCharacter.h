// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Character/GameCharacterBase.h"
#include "GameCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API AGameCharacter : public AGameCharacterBase
{
	GENERATED_BODY()

public:
	AGameCharacter();
	virtual void Tick(float DeltaTime) override;;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;
	


	
};
