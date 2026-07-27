#include "BlackoutThrowable.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

ABlackoutThrowable::ABlackoutThrowable()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(12.0f);
	CollisionComp->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	FuseTime = 3.0f;
	ExplosionRadius = 800.0f;
	ExplosionMaxDamage = 150.0f;
}

void ABlackoutThrowable::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FuseTimerHandle, this, &ABlackoutThrowable::Explode, FuseTime, false);
}

void ABlackoutThrowable::Explode()
{
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionMaxDamage, GetActorLocation(), ExplosionRadius, UDamageType::StaticClass(), IgnoredActors, GetInstigator(), GetInstigatorController(), true);

	Destroy();
}
