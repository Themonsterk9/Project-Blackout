#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackoutWeaponBase.h"
#include "BlackoutWeaponManager.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackoutWeaponManagerComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Inventory")
	TArray<TSubclassOf<ABlackoutWeaponBase>> DefaultWeaponClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Inventory")
	TArray<ABlackoutWeaponBase*> EquippedWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Inventory")
	int32 CurrentWeaponIndex;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory")
	void EquipWeaponSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory")
	ABlackoutWeaponBase* GetActiveWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory")
	void StartFireActiveWeapon();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory")
	void StopFireActiveWeapon();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory")
	void ReloadActiveWeapon();
};
