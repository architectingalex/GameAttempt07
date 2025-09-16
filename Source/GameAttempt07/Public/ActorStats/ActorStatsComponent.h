// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEATTEMPT07_API UActorStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CurrentHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CurrentStamina = 100.f;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
