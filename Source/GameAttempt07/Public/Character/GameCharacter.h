// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Character/GameCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Equipment/EquipmentComponent.h"
#include "Interaction/InteractionComponent.h"
#include "ActorStats/ActorStatsComponent.h"
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UEquipmentComponent* EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UActorStatsComponent* ActorStatsComponent;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;


	


	
};
