// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/GameWidgetController.h"
#include "ActorStats/ActorStatsComponent.h"
#include "Interactable/InteractableStructs.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPrimaryEquipmentChanged, FInteractableEquipmentStruct, NewSlotInfo);



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEATTEMPT07_API UOverlayWidgetController : public UGameWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues()override;
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Equipment")
	FOnPrimaryEquipmentChanged OnPrimaryEquipmentChanged;

	UFUNCTION()
	void HandleEquipmentSlotChanged(FInteractableEquipmentStruct NewSlotInfo);

	
};
