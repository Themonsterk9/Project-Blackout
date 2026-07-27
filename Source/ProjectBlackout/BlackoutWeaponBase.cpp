#include "BlackoutWeaponBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ABlackoutWeaponBase::ABlackoutWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponName = TEXT("M4A1 Tactical");
	FireMode = EBlackoutFireMode::Automatic;
	BaseDamage = 32.0f;
	HeadshotMultiplier = 2.5f;
	FireRateRPM = 750.0f;
	MagazineCapacity = 30;
	CurrentAmmoInMag = MagazineCapacity;
	TotalReserveAmmo = 120;
	RecoilVertical = 1.2f;
	RecoilHorizontal = 0.4f;
	ReloadDuration = 2.2f;

	bIsReloading = false;
	bIsAiming = false;
}

void ABlackoutWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoInMag = MagazineCapacity;
}

void ABlackoutWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackoutWeaponBase::StartFire()
{
	if (bIsReloading || CurrentAmmoInMag <= 0)
	{
		if (CurrentAmmoInMag <= 0 && !bIsReloading)
		{
			StartReload();
		}
		return;
	}

	PerformSingleShot();

	if (FireMode == EBlackoutFireMode::Automatic)
	{
		const float FireInterval = 60.0f / FireRateRPM;
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ABlackoutWeaponBase::PerformSingleShot, FireInterval, true);
	}
}

void ABlackoutWeaponBase::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ABlackoutWeaponBase::PerformSingleShot()
{
	if (CurrentAmmoInMag <= 0)
	{
		StopFire();
		StartReload();
		return;
	}

	CurrentAmmoInMag--;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		OwnerPawn->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		const float Spread = bIsAiming ? 0.2f : 1.2f;
		const FVector AimDir = CameraRotation.Vector();
		const FVector RandomSpread = FMath::VRand() * Spread;
		const FVector TraceEnd = CameraLocation + (AimDir + RandomSpread).GetSafeNormal() * 10000.0f;

		FHitResult Hit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(OwnerPawn);

		if (GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			float FinalDamage = BaseDamage;
			if (Hit.BoneName == FName("head"))
			{
				FinalDamage *= HeadshotMultiplier;
			}

			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), FinalDamage, AimDir, Hit, OwnerPawn->GetController(), this, UDamageType::StaticClass());
		}

		ApplyRecoil();
	}
}

void ABlackoutWeaponBase::ApplyRecoil()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn && OwnerPawn->GetController())
	{
		const float PitchRecoil = -RecoilVertical;
		const float YawRecoil = FMath::FRandRange(-RecoilHorizontal, RecoilHorizontal);
		OwnerPawn->AddControllerPitchInput(PitchRecoil);
		OwnerPawn->AddControllerYawInput(YawRecoil);
	}
}

void ABlackoutWeaponBase::StartReload()
{
	if (bIsReloading || CurrentAmmoInMag >= MagazineCapacity || TotalReserveAmmo <= 0)
	{
		return;
	}

	bIsReloading = true;
	StopFire();

	GetWorldTimerManager().SetTimer(ReloadTimerHandle, [this]()
	{
		const int32 AmmoNeeded = MagazineCapacity - CurrentAmmoInMag;
		const int32 AmmoToTransfer = FMath::Min(AmmoNeeded, TotalReserveAmmo);

		CurrentAmmoInMag += AmmoToTransfer;
		TotalReserveAmmo -= AmmoToTransfer;
		bIsReloading = false;
	}, ReloadDuration, false);
}

void ABlackoutWeaponBase::SetAiming(bool bNewAiming)
{
	bIsAiming = bNewAiming;
}
