// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interactable/Equipment/EquipmentEnums.h" // <-- include your enum
#include "EquipmentHelpers.generated.h"

UCLASS()
class GAMEATTEMPT07_API UEquipmentHelpers : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    /** Equipment Name conversions */
    UFUNCTION(BlueprintPure, Category="Equipment")
    static FString EquipmentNameToString(EEquipmentName InEnum);
    
    UFUNCTION(BlueprintPure, Category="Equipment")
    static FText EquipmentNameToDisplayName(EEquipmentName InEnum);


    /** Equipment Slot conversions */
    UFUNCTION(BlueprintPure, Category="Equipment")
    static FString EquipmentSlotToString(EEquipmentSlot InEnum);

    UFUNCTION(BlueprintPure, Category="Equipment")
    static FText EquipmentSlotToDisplayName(EEquipmentSlot InEnum);
};
