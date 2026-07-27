#pragma once

#include "CoreMinimal.h"
#include "BlackoutGameMode.h"
#include "GameFramework/Actor.h"
#include "BlackoutGameModes.generated.h"

/** Capture Zone Actor for Domination Game Mode */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutCaptureZone : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutCaptureZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Zone")
	FString ZoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Zone")
	int32 ControllingTeamID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Zone")
	float CaptureProgress;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Zone")
	void UpdateCapture(int32 TeamID, float DeltaProgress);
};

/** 1. Team Deathmatch (TDM) */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_TDM : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_TDM();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | TDM")
	int32 TargetKillsToWin;

	UFUNCTION(BlueprintCallable, Category = "Blackout | TDM")
	void AddKillScore(int32 ScoringTeamID);
};

/** 2. Free For All (FFA) */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_FFA : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_FFA();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | FFA")
	int32 ScoreLimitToWin;
};

/** 3. Domination */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_Domination : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_Domination();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Domination")
	int32 TargetPointsToWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Domination")
	TArray<ABlackoutCaptureZone*> CaptureZones;
};

/** 4. Search & Destroy (SnD) */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_SnD : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_SnD();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | SnD")
	float BombPlantDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | SnD")
	float BombDefuseDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | SnD")
	float RoundTimeSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | SnD")
	bool bIsBombPlanted;
};

/** 5. Battle Royale (BR) */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_BattleRoyale : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_BattleRoyale();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | BR")
	float SafeZoneRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | BR")
	float ShrinkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | BR")
	int32 AlivePlayersCount;

	UFUNCTION(BlueprintCallable, Category = "Blackout | BR")
	void OnPlayerEliminated(AController* EliminatedController);
};

/** 6. Offline Practice Mode */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode_Practice : public ABlackoutGameMode
{
	GENERATED_BODY()

public:
	ABlackoutGameMode_Practice();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Practice")
	int32 BotCountToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Practice")
	void SpawnPracticeBots();
};
