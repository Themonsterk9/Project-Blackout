#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackoutMeleeComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackoutMeleeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Melee")
	float MeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Melee")
	float MeleeReachDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Melee")
	float MeleeCooldown;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Melee")
	bool PerformMeleeAttack();

private:
	bool bCanMelee;
	FTimerHandle MeleeTimerHandle;
};
