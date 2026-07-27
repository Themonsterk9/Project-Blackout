#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BlackoutThrowable.generated.h"

UCLASS()
class PROJECTBLACKOUT_API ABlackoutThrowable : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutThrowable();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Grenade")
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Grenade")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Grenade")
	float FuseTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Grenade")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Grenade")
	float ExplosionMaxDamage;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Grenade")
	void Explode();

private:
	FTimerHandle FuseTimerHandle;
};
