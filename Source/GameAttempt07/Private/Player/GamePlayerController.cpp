// Copyright Big Rocket Games


#include "Player/GamePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/InteractionComponent.h"

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
	//*	FInputModeGameAndUI InputModeData;
	//* InputModeData.SetLockMouseToViewportBehavior((EMouseLockMode::DoNotLock));
	//* SetInputMode(InputModeData);

	
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGamePlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGamePlayerController::Look);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGamePlayerController::Interact);

	
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
