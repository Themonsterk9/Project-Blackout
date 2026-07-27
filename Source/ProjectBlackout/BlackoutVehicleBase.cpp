#include "BlackoutVehicleBase.h"
#include "Kismet/GameplayStatics.h"

ABlackoutVehicleBase::ABlackoutVehicleBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	VehicleName = TEXT("Armored Scout Car");
	VehicleType = EBlackoutVehicleType::Car;
	MaxHealth = 500.0f;
	Health = MaxHealth;
	MaxFuel = 100.0f;
	Fuel = MaxFuel;
	CurrentSpeedKmh = 0.0f;
}

void ABlackoutVehicleBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackoutVehicleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlackoutVehicleBase, Health);
	DOREPLIFETIME(ABlackoutVehicleBase, Fuel);
	DOREPLIFETIME(ABlackoutVehicleBase, CurrentSpeedKmh);
	DOREPLIFETIME(ABlackoutVehicleBase, Occupants);
}

void ABlackoutVehicleBase::Accelerate(float Value)
{
	if (Fuel > 0.0f && Health > 0.0f)
	{
		CurrentSpeedKmh = FMath::Clamp(CurrentSpeedKmh + (Value * 5.0f), -30.0f, 120.0f);
		Fuel = FMath::Clamp(Fuel - 0.01f, 0.0f, MaxFuel);
	}
}

void ABlackoutVehicleBase::Steer(float Value)
{
	AddActorLocalRotation(FRotator(0.0f, Value * 2.0f, 0.0f));
}

void ABlackoutVehicleBase::Brake()
{
	CurrentSpeedKmh = FMath::FInterpTo(CurrentSpeedKmh, 0.0f, GetWorld()->GetDeltaSeconds(), 5.0f);
}

bool ABlackoutVehicleBase::EnterVehicle(APawn* Passenger)
{
	if (Passenger && Occupants.Num() < 4)
	{
		Occupants.Add(Passenger);
		Passenger->SetActorHiddenInGame(true);
		Passenger->SetActorEnableCollision(false);
		return true;
	}
	return false;
}

bool ABlackoutVehicleBase::ExitVehicle(APawn* Passenger)
{
	if (Passenger && Occupants.Contains(Passenger))
	{
		Occupants.Remove(Passenger);
		Passenger->SetActorLocation(GetActorLocation() + GetActorRightVector() * 200.0f);
		Passenger->SetActorHiddenInGame(false);
		Passenger->SetActorEnableCollision(true);
		return true;
	}
	return false;
}

void ABlackoutVehicleBase::ApplyVehicleDamage(float DamageAmount)
{
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	if (Health <= 0.0f)
	{
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 200.0f, GetActorLocation(), 600.0f, UDamageType::StaticClass(), TArray<AActor*>(), this, GetInstigatorController());
	}
}

ABlackoutCar::ABlackoutCar()
{
	VehicleType = EBlackoutVehicleType::Car;
	VehicleName = TEXT("Tactical Offroad Buggy");
}

ABlackoutMotorcycle::ABlackoutMotorcycle()
{
	VehicleType = EBlackoutVehicleType::Motorcycle;
	VehicleName = TEXT("Tactical Enduro Bike");
	LeanAngle = 0.0f;
}

ABlackoutBoat::ABlackoutBoat()
{
	VehicleType = EBlackoutVehicleType::Boat;
	VehicleName = TEXT("Rigid Inflatable Boat (RIB)");
	BuoyancyForce = 1000.0f;
}

ABlackoutHelicopter::ABlackoutHelicopter()
{
	VehicleType = EBlackoutVehicleType::Helicopter;
	VehicleName = TEXT("Tactical Transport Helicopter");
	RotorSpeed = 0.0f;
}

void ABlackoutHelicopter::ApplyAscent(float Value)
{
	AddActorLocalOffset(FVector(0.0f, 0.0f, Value * 10.0f));
}
