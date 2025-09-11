// Copyright Big Rocket Games


#include "Interaction/InteractionComponent.h"
#include "Components/SphereComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		if (OverlappedInteractables.Num() == 0)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Cyan, TEXT("OverlappedInteractables: None"));
		}
		else
		{
			int32 MsgKey = 10;
			for (const TScriptInterface<IInteractInterface>& Item : OverlappedInteractables)
			{
				if (Item.GetObject())
				{
					bool bIsCurrent = (Item.GetObject() == CurrentInteractionObject.GetObject());

					FString DebugString;
					if (bIsCurrent)
					{
						DebugString = FString(">>> Current: ") + Item.GetObject()->GetName() + FString(" <<<");
					}
					else
					{
						DebugString = FString("Overlapped: ") + Item.GetObject()->GetName();
					}

					FColor TextColor = bIsCurrent ? FColor::Red : FColor::Cyan;

					GEngine->AddOnScreenDebugMessage(MsgKey++, 0.f, TextColor, DebugString);
				}
			}
		}
	}

}

void UInteractionComponent::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		TScriptInterface<IInteractInterface> Interactable;
		Interactable.SetObject(OtherActor);
		Interactable.SetInterface(Cast<IInteractInterface>(OtherActor));
		OverlappedInteractables.AddUnique(Interactable);

		if (!CurrentInteractionObject)
		{
			CurrentInteractionObject = Interactable;
			IInteractInterface::Execute_HighlightActor(OtherActor);
			
		}
	}

}

void UInteractionComponent::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		TScriptInterface<IInteractInterface> Interactable;
		Interactable.SetObject(OtherActor);
		Interactable.SetInterface(Cast<IInteractInterface>(OtherActor));

		OverlappedInteractables.RemoveAll(
	[OtherActor](const TScriptInterface<IInteractInterface>& Item)
	{
		return Item.GetObject() == OtherActor;
	}
);

		if (CurrentInteractionObject.GetObject() == OtherActor)
		{
			IInteractInterface::Execute_UnHighlightActor(OtherActor);
			CurrentInteractionObject = nullptr;
			
			if (OverlappedInteractables.Num() > 0)
			{
				CurrentInteractionObject = OverlappedInteractables[0];
				IInteractInterface::Execute_HighlightActor(CurrentInteractionObject.GetObject());

			}
		}
	}

}



