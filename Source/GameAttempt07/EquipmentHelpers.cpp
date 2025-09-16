// Copyright Big Rocket Games

#include "EquipmentHelpers.h"

FString UEquipmentHelpers::EquipmentNameToString(EEquipmentName InEnum)
{
	return UEnum::GetValueAsString(InEnum);
}

FText UEquipmentHelpers::EquipmentNameToDisplayName(EEquipmentName InEnum)
{
	return UEnum::GetDisplayValueAsText(InEnum);
}

FString UEquipmentHelpers::EquipmentSlotToString(EEquipmentSlot InEnum)
{
	return UEnum::GetValueAsString(InEnum);
}

FText UEquipmentHelpers::EquipmentSlotToDisplayName(EEquipmentSlot InEnum)
{
	return UEnum::GetDisplayValueAsText(InEnum);
}