// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Interactable/InteractableStructs.h"
#include "UObject/NoExportTypes.h"
#include "GameWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentSlotDataReady, FInteractableEquipmentStruct, SlotData);

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC) : PlayerController(PC) {}

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> PlayerController;
	
};

/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API UGameWidgetController : public UObject
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BroadcastInitialValues();
	
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	

	



	
};
