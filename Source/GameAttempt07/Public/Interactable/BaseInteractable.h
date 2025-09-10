// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "BaseInteractable.generated.h"

UCLASS()
class GAMEATTEMPT07_API ABaseInteractable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseInteractable();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
