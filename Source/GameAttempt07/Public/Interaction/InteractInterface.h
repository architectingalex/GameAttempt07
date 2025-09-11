// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None UMETA(DisplayName = "None"),
	Pickup UMETA(DisplayName = "Pickup"),
	Door UMETA(DisplayName = "Door"),
	Dialogue UMETA(DisplayName = "Dialogue"),
	Vehicle UMETA(DisplayName = "Vehicle"),

	MAX UMETA(Hidden)
};

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEATTEMPT07_API IInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void HighlightActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void UnHighlightActor();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void InteractWithObject(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	EInteractionType GetInteractionType() const;
	
	
};
