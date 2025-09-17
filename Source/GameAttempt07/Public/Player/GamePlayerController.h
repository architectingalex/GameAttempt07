// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GamePlayerController.generated.h"



class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


/**
 * 
 */
UCLASS()
class GAMEATTEMPT07_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	AGamePlayerController();
	virtual void Tick(float DeltaTime) override;
	void HideMenuReleased (const FInputActionValue& InputActionValue);
	void HideMenu ();
	void HideMenuClicked ();

	
	
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GameContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DropAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShowMenuAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> HideMenuAction;

	void Move(const FInputActionValue& InputActionValue);
	void Look (const FInputActionValue& InputActionValue);
	void Interact (const FInputActionValue& InputActionValue);
	void Drop (const FInputActionValue& InputActionValue);
	void ShowMenu (const FInputActionValue& InputActionValue);



	
	// GamePlayerController.h
	bool bMenuOpen = false;
	bool bShiftHeld = false;

	bool bMenuClosedByClick = false; // NEW





};
