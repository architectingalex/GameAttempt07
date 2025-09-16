// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable/InteractableStructs.h"
#include "GameUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, FInteractableEquipmentStruct, SlotData);

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API UGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UPROPERTY(BlueprintAssignable, Category="UI")
	FOnSlotClicked OnSlotClicked;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	UFUNCTION(BlueprintCallable)
	void HandleSlotClicked(FInteractableEquipmentStruct SlotData);

	
};
