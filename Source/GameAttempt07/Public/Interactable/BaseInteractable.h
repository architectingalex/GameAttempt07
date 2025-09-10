// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "BaseInteractable.generated.h"

UCLASS()
class GAMEATTEMPT07_API ABaseInteractable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseInteractable();

	virtual void Tick(float DeltaTime) override;

	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* CollisionSphere;

protected:
	virtual void BeginPlay() override;

};

