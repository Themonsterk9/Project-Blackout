#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackoutWeaponBase.generated.h"

UENUM(BlueprintType)
enum class EBlackoutFireMode : uint8
{
	Single     UMETA(DisplayName = "Single Fire"),
	Burst      UMETA(DisplayName = "Burst Fire"),
	Automatic  UMETA(DisplayName = "Automatic Fire")
};

UCLASS()
class PROJECTBLACKOUT_API ABlackoutWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutWeaponBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Weapon Properties */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	EBlackoutFireMode FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float HeadshotMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float FireRateRPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	int32 MagazineCapacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Weapon Specs")
	int32 CurrentAmmoInMag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	int32 TotalReserveAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float RecoilVertical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float RecoilHorizontal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Specs")
	float ReloadDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Weapon Specs")
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Weapon Specs")
	bool bIsAiming;

	/** Combat Actions */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Weapon Actions")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Weapon Actions")
	void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Weapon Actions")
	void StartReload();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Weapon Actions")
	void SetAiming(bool bNewAiming);

protected:
	void PerformSingleShot();
	void ApplyRecoil();

	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
};
