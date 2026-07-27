#include "BlackoutWeaponManager.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

UBlackoutWeaponManagerComponent::UBlackoutWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentWeaponIndex = 0;
}

void UBlackoutWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		for (TSubclassOf<ABlackoutWeaponBase> WeaponClass : DefaultWeaponClasses)
		{
			if (WeaponClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Owner;
				SpawnParams.Instigator = Cast<APawn>(Owner);
				ABlackoutWeaponBase* NewWeapon = GetWorld()->SpawnActor<ABlackoutWeaponBase>(WeaponClass, SpawnParams);
				if (NewWeapon)
				{
					EquippedWeapons.Add(NewWeapon);
				}
			}
		}
	}
}

void UBlackoutWeaponManagerComponent::EquipWeaponSlot(int32 SlotIndex)
{
	if (EquippedWeapons.IsValidIndex(SlotIndex))
	{
		CurrentWeaponIndex = SlotIndex;
	}
}

ABlackoutWeaponBase* UBlackoutWeaponManagerComponent::GetActiveWeapon() const
{
	if (EquippedWeapons.IsValidIndex(CurrentWeaponIndex))
	{
		return EquippedWeapons[CurrentWeaponIndex];
	}
	return nullptr;
}

void UBlackoutWeaponManagerComponent::StartFireActiveWeapon()
{
	ABlackoutWeaponBase* Weapon = GetActiveWeapon();
	if (Weapon)
	{
		Weapon->StartFire();
	}
}

void UBlackoutWeaponManagerComponent::StopFireActiveWeapon()
{
	ABlackoutWeaponBase* Weapon = GetActiveWeapon();
	if (Weapon)
	{
		Weapon->StopFire();
	}
}

void UBlackoutWeaponManagerComponent::ReloadActiveWeapon()
{
	ABlackoutWeaponBase* Weapon = GetActiveWeapon();
	if (Weapon)
	{
		Weapon->StartReload();
	}
}
