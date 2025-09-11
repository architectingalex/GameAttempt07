// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "EquipmentTypes.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	None       UMETA(DisplayName = "None"),
	Primary    UMETA(DisplayName = "Primary Weapon"),
	Secondary  UMETA(DisplayName = "Secondary Weapon"),
	Melee      UMETA(DisplayName = "Melee"),
	Explosive	UMETA(DisplayName = "Explosive"),
	Scanner    UMETA(DisplayName = "Scanner"),
	Traversal   UMETA(DisplayName = "Traversal"),
	Camp		UMETA(DisplayName = "Camp"),

	MAX        UMETA(Hidden)
};
