#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "BlackoutVehicleBase.generated.h"

UENUM(BlueprintType)
enum class EBlackoutVehicleType : uint8
{
	Car         UMETA(DisplayName = "Tactical Car"),
	Motorcycle  UMETA(DisplayName = "Motorcycle"),
	Boat        UMETA(DisplayName = "Speed Boat"),
	Helicopter  UMETA(DisplayName = "Helicopter")
};

UCLASS()
class PROJECTBLACKOUT_API ABlackoutVehicleBase : public APawn
{
	GENERATED_BODY()

public:
	ABlackoutVehicleBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle")
	FString VehicleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle")
	EBlackoutVehicleType VehicleType;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle Specs")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle Specs")
	float MaxHealth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle Specs")
	float Fuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Vehicle Specs")
	float MaxFuel;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Vehicle State")
	float CurrentSpeedKmh;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Vehicle Occupants")
	TArray<APawn*> Occupants;

	/** Vehicle Controls */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Controls")
	virtual void Accelerate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Controls")
	virtual void Steer(float Value);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Controls")
	virtual void Brake();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Actions")
	bool EnterVehicle(APawn* Passenger);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Actions")
	bool ExitVehicle(APawn* Passenger);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Vehicle Damage")
	void ApplyVehicleDamage(float DamageAmount);
};

/** Car Vehicle */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutCar : public ABlackoutVehicleBase
{
	GENERATED_BODY()

public:
	ABlackoutCar();
};

/** Motorcycle Vehicle */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutMotorcycle : public ABlackoutVehicleBase
{
	GENERATED_BODY()

public:
	ABlackoutMotorcycle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Bike")
	float LeanAngle;
};

/** Boat Vehicle */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutBoat : public ABlackoutVehicleBase
{
	GENERATED_BODY()

public:
	ABlackoutBoat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Boat")
	float BuoyancyForce;
};

/** Helicopter Vehicle */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutHelicopter : public ABlackoutVehicleBase
{
	GENERATED_BODY()

public:
	ABlackoutHelicopter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Helicopter")
	float RotorSpeed;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Helicopter Controls")
	void ApplyAscent(float Value);
};
