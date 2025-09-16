// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/GameUserWidget.h"
#include "Interactable/InteractableStructs.h"
#include "EquipmentSlotWidget.generated.h"

UCLASS()
class GAMEATTEMPT07_API UEquipmentSlotWidget : public UGameUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipment")
	EEquipmentSlot SlotType;
	
	UPROPERTY(BlueprintReadOnly, Category="Equipment")
	FInteractableEquipmentStruct CurrentSlotData;
	
	virtual void SetWidgetController(UObject* InWidgetController) override;
	
	UFUNCTION()
	void HandleEquipmentChanged(EEquipmentSlot ChangedSlot, FInteractableEquipmentStruct NewSlotInfo);
	
	UFUNCTION(BlueprintCallable)
	void HandleButtonClicked();
};
