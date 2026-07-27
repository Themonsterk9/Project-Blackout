#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "BlackoutMapFramework.generated.h"

UENUM(BlueprintType)
enum class EBlackoutMapType : uint8
{
	TrainingGround     UMETA(DisplayName = "Training Ground"),
	SmallMP            UMETA(DisplayName = "Small MP Map (Factory)"),
	MediumMP           UMETA(DisplayName = "Medium MP Map (District)"),
	LargeOpenWorld     UMETA(DisplayName = "Large Open World Map"),
	BattleRoyale       UMETA(DisplayName = "Battle Royale Map (Island)")
};

UENUM(BlueprintType)
enum class EBlackoutWeatherType : uint8
{
	Clear  UMETA(DisplayName = "Clear Sky"),
	Rain   UMETA(DisplayName = "Rainstorm"),
	Fog    UMETA(DisplayName = "Dense Fog"),
	Storm  UMETA(DisplayName = "Thunderstorm")
};

/** Team Spawn Point Actor */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutSpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Spawn")
	int32 TeamID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Spawn")
	bool bIsOccupied;
};

/** Environment System Controller (Lighting, Day/Night, Weather, Fog) */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutEnvironmentSystem : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutEnvironmentSystem();

protected:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Environment", meta=(ClampMin=0.0, ClampMax=24.0))
	float TimeOfDayHours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Environment")
	bool bAnimateDayNightCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Environment")
	EBlackoutWeatherType CurrentWeather;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Environment")
	void SetWeather(EBlackoutWeatherType NewWeather);
};

/** Map Descriptor Data Asset */
UCLASS(BlueprintType)
class PROJECTBLACKOUT_API UBlackoutMapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Map Specs")
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Map Specs")
	EBlackoutMapType MapType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Map Specs")
	int32 MaxRecommendedPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Map Specs")
	FText MapDescription;
};
