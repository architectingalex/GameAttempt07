// Copyright Big Rocket Games


#include "Player/GamePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Equipment/EquipmentComponent.h"
#include "Interaction/InteractionComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "UI/HUD/GameHUD.h"

AGamePlayerController::AGamePlayerController()
{
	bReplicates = true;
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GameContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(GameContext, 0);

	bShowMouseCursor = false;
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGamePlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGamePlayerController::Look);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGamePlayerController::Interact);
	EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AGamePlayerController::Drop);
	EnhancedInputComponent->BindAction(ShowMenuAction, ETriggerEvent::Started, this, &AGamePlayerController::ShowMenu);
	EnhancedInputComponent->BindAction(HideMenuAction, ETriggerEvent::Started, this, &AGamePlayerController::HideMenuReleased);
	
}

void AGamePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AGamePlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y); 
}

void AGamePlayerController::Interact(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (UInteractionComponent* InteractionComponent = ControlledPawn->FindComponentByClass<UInteractionComponent>())
		{
			if (InteractionComponent->CurrentInteractionObject)
			{
				UObject* Target = InteractionComponent->CurrentInteractionObject.GetObject();
				
				const EInteractionType Type = IInteractInterface::Execute_GetInteractionType(Target);
				
				switch (Type)
				{
				case EInteractionType::Pickup:
					IInteractInterface::Execute_InteractWithObject(Target, ControlledPawn);
					break;

				case EInteractionType::Door:
					IInteractInterface::Execute_InteractWithObject(Target, ControlledPawn);
					break;

				case EInteractionType::Dialogue:
					IInteractInterface::Execute_InteractWithObject(Target, ControlledPawn);
					break;

				case EInteractionType::Vehicle:
					IInteractInterface::Execute_InteractWithObject(Target, ControlledPawn);
					break;

				case EInteractionType::None:
				default:
					IInteractInterface::Execute_InteractWithObject(Target, ControlledPawn);
					break;
				}
			}
			
		}
	}
}

void AGamePlayerController::Drop(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (UEquipmentComponent* EquipmentComponent = ControlledPawn->FindComponentByClass<UEquipmentComponent>())
		{
			EquipmentComponent->UnequipActiveItem();
		}
	}
}

void AGamePlayerController::ShowMenu(const FInputActionValue& InputActionValue)
{
	if (bMenuOpen || bMenuClosedByClick) return;
	
	if (bMenuClosedByClick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowMenu ignored because menu was closed by click"));
		return;
	}
	if (bMenuOpen)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowMenu called but bMenuOpen is already true — ignoring"));
		return;
	}

	bShiftHeld = true;
	bMenuClosedByClick = false;

	UE_LOG(LogTemp, Warning, TEXT("ShowMenu called: ShiftHeld=%d, MenuClosedByClick=%d"), bShiftHeld, bMenuClosedByClick);
	
	if (AGameHUD* GameHUD = Cast<AGameHUD>(GetHUD()))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameHUD found, toggling equipment menu visible"));
		GameHUD->ToggleEquipmentMenu(true);
		bShowMouseCursor = true;
		bEnableClickEvents = true;      
		bEnableMouseOverEvents = true;
		UE_LOG(LogTemp, Warning, TEXT("Mouse: Cursor=%d, ClickEvents=%d, HoverEvents=%d"),
	bShowMouseCursor, bEnableClickEvents, bEnableMouseOverEvents);
		
		if (UUserWidget* Menu = GameHUD->GetEquipmentMenuWidget())
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		this,
		Menu,
		EMouseLockMode::DoNotLock,
		false
			);

			// Defer focus until next tick
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, [this, Menu]()
			{
				if (IsValid(Menu))
				{
					Menu->SetKeyboardFocus(); // stronger than SetFocus
					UE_LOG(LogTemp, Warning, TEXT("Focus applied to %s: HasFocus=%d"),
						*Menu->GetName(),
						Menu->HasUserFocus(this));
				}
			}, 0.0f, false); // 0.0f = next frame
		}
		
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GetEquipmentMenuWidget() returned NULL"));
		}
		
		SetIgnoreLookInput(true);
		SetIgnoreMoveInput(true);
		UE_LOG(LogTemp, Warning, TEXT("Input ignored: Look=%d, Move=%d"),
			IsLookInputIgnored(), IsMoveInputIgnored());


		bMenuOpen = true;
		bMenuClosedByClick = false;
		UE_LOG(LogTemp, Warning, TEXT("Menu state set: bMenuOpen=%d, bMenuClosedByClick=%d"),
			bMenuOpen, bMenuClosedByClick);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetHUD() cast to AGameHUD failed"));
	}
}


void AGamePlayerController::HideMenuReleased(const FInputActionValue& InputActionValue)
{
	if (!bMenuOpen) return; 
	UE_LOG(LogTemp, Warning, TEXT("HideMenuReleased fired. Value=%s, bMenuOpen=%d, ClosedByClick=%d"), 
		*InputActionValue.ToString(), bMenuOpen, bMenuClosedByClick);

	bShiftHeld = false;

	if (bMenuOpen)
	{
		HideMenu();
	}

	// ✅ Always reset here so ShowMenu isn’t blocked next time
	bMenuClosedByClick = false;
	UE_LOG(LogTemp, Warning, TEXT("HideMenuReleased -> bMenuClosedByClick reset"));
}

void AGamePlayerController::HideMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("HideMenu called"));

	if (AGameHUD* GameHUD = Cast<AGameHUD>(GetHUD()))
	{
		GameHUD->ToggleEquipmentMenu(false);

		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

		SetIgnoreLookInput(false);
		SetIgnoreMoveInput(false);

		bMenuOpen = false; 
		bMenuClosedByClick = false; // <-- reset here always

		UE_LOG(LogTemp, Warning, TEXT("Menu hidden, state reset"));
	}
	
}

void AGamePlayerController::HideMenuClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("HideMenuClicked called: MenuOpen=%d"), bMenuOpen);

	if (bMenuOpen)
	{
		HideMenu();
		//bMenuClosedByClick = true;
		UE_LOG(LogTemp, Warning, TEXT("Menu closed by click, bMenuClosedByClick=%d"), bMenuClosedByClick);
	}
}
