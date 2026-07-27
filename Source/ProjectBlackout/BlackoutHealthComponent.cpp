#include "BlackoutHealthComponent.h"
#include "GameFramework/Actor.h"

UBlackoutHealthComponent::UBlackoutHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	MaxArmor = 100.0f;
	CurrentArmor = MaxArmor;
}

void UBlackoutHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentArmor = MaxArmor;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakePointDamage.AddDynamic(this, &UBlackoutHealthComponent::HandleTakePointDamage);
	}
}

void UBlackoutHealthComponent::HandleTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (CurrentHealth <= 0.0f || Damage <= 0.0f)
	{
		return;
	}

	float AdjustedDamage = Damage;
	if (BoneName == FName("head"))
	{
		AdjustedDamage *= 2.5f;
	}
	else if (BoneName.ToString().Contains(TEXT("leg")) || BoneName.ToString().Contains(TEXT("arm")))
	{
		AdjustedDamage *= 0.75f;
	}

	// Armor mitigation (70% absorbed by armor if available)
	if (CurrentArmor > 0.0f)
	{
		const float ArmorAbsorbed = FMath::Min(CurrentArmor, AdjustedDamage * 0.7f);
		CurrentArmor -= ArmorAbsorbed;
		AdjustedDamage -= ArmorAbsorbed;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - AdjustedDamage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.0f)
	{
		AActor* Killer = InstigatedBy ? InstigatedBy->GetPawn() : DamageCauser;
		OnDeath.Broadcast(Killer);
	}
}

void UBlackoutHealthComponent::Heal(float HealAmount)
{
	if (CurrentHealth > 0.0f && HealAmount > 0.0f)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
		OnHealthChanged.Broadcast(CurrentHealth);
	}
}
