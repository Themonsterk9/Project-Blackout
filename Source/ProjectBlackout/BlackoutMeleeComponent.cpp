#include "BlackoutMeleeComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

UBlackoutMeleeComponent::UBlackoutMeleeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MeleeDamage = 60.0f;
	MeleeReachDistance = 150.0f;
	MeleeCooldown = 0.8f;
	bCanMelee = true;
}

bool UBlackoutMeleeComponent::PerformMeleeAttack()
{
	if (!bCanMelee)
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character)
	{
		bCanMelee = false;

		FVector EyeLocation;
		FRotator EyeRotation;
		Character->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		const FVector EndLocation = EyeLocation + EyeRotation.Vector() * MeleeReachDistance;

		FHitResult Hit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Character);

		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, EndLocation, ECC_Pawn, QueryParams))
		{
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), MeleeDamage, EyeRotation.Vector(), Hit, Character->GetController(), Character, UDamageType::StaticClass());
		}

		GetWorld()->GetTimerManager().SetTimer(MeleeTimerHandle, [this]()
		{
			bCanMelee = true;
		}, MeleeCooldown, false);

		return true;
	}

	return false;
}
