// Copyright Big Rocket Games

#pragma once

#include "CoreMinimal.h"
#include "EquipmentEnums.generated.h"

UENUM(BlueprintType)
enum class EEquipmentUsageState : uint8
{
	Empty        UMETA(DisplayName = "Empty"),
	Holster     UMETA(DisplayName = "Holster"),
	InUse   UMETA(DisplayName = "InUse"),

	MAX UMETA(Hidden)

};

UENUM(BlueprintType)
enum class EEquipmentName : uint8
{
	None		UMETA(DisplayName = "None"),
	Pistol        UMETA(DisplayName = "Pistol"),
	Rifle     UMETA(DisplayName = "Rifle"),
	Shotgun   UMETA(DisplayName = "Shotgun"),
	Sniper		UMETA(DisplayName = "Sniper"),
	RocketLauncher		UMETA(DisplayName = "RocketLauncher"),
	Grenade		UMETA(DisplayName = "Grenade"),

	MAX UMETA(Hidden)

};
