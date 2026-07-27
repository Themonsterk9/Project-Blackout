#include "BlackoutCustomizationSystem.h"

UBlackoutCustomizationComponent::UBlackoutCustomizationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	FacePresetID = 0;
	SkinToneID = 1;
	HairStyleID = 2;
	OutfitID = TEXT("Outfit_SpecOps");

	ActiveLoadoutIndex = 0;
	EquippedEmotes.Init(TEXT("Emote_Salute"), 8);

	for (int32 i = 0; i < 5; ++i)
	{
		FBlackoutLoadout L;
		L.LoadoutName = FString::Printf(TEXT("Loadout %d"), i + 1);
		SavedLoadouts.Add(L);
	}
}

void UBlackoutCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBlackoutCustomizationComponent::EquipWeaponSkin(FString WeaponID, FString SkinID)
{
	WeaponSkins.Add(WeaponID, SkinID);
}

void UBlackoutCustomizationComponent::SelectLoadout(int32 SlotIndex)
{
	if (SavedLoadouts.IsValidIndex(SlotIndex))
	{
		ActiveLoadoutIndex = SlotIndex;
	}
}

void UBlackoutCustomizationComponent::SaveLoadout(int32 SlotIndex, const FBlackoutLoadout& NewLoadout)
{
	if (SavedLoadouts.IsValidIndex(SlotIndex))
	{
		SavedLoadouts[SlotIndex] = NewLoadout;
	}
}
