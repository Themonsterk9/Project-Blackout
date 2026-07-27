#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackoutHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, Killer);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackoutHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Armor")
	float MaxArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Armor")
	float CurrentArmor;

	UPROPERTY(BlueprintAssignable, Category = "Blackout | Events")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Blackout | Events")
	FOnDeathSignature OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Damage")
	void HandleTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Health")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Health")
	bool IsDead() const { return CurrentHealth <= 0.0f; }
};
