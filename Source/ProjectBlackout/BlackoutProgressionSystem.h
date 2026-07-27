#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackoutProgressionSystem.generated.h"

UENUM(BlueprintType)
enum class EBlackoutCompetitiveRank : uint8
{
	Bronze       UMETA(DisplayName = "Bronze"),
	Silver       UMETA(DisplayName = "Silver"),
	Gold         UMETA(DisplayName = "Gold"),
	Platinum     UMETA(DisplayName = "Platinum"),
	Diamond      UMETA(DisplayName = "Diamond"),
	Master       UMETA(DisplayName = "Master"),
	Grandmaster  UMETA(DisplayName = "Grandmaster")
};

USTRUCT(BlueprintType)
struct FBlackoutPlayerStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 MatchesPlayed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Wins = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Losses = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Kills = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Deaths = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Assists = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 Headshots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	float AccuracyRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	float TimePlayedSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	float DistanceTraveledMeters = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Stats")
	int32 RevivesCount = 0;
};

USTRUCT(BlueprintType)
struct FBlackoutDailyMission
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	FString MissionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	int32 TargetProgress = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	int32 CurrentProgress = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	int32 RewardXP = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Mission")
	bool bIsCompleted = false;
};

USTRUCT(BlueprintType)
struct FBlackoutAchievement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	FString AchievementID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	FString Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	int32 TargetValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	int32 CurrentProgress = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Achievement")
	bool bIsUnlocked = false;
};

UCLASS()
class PROJECTBLACKOUT_API UBlackoutProgressionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutProgressionSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Level & XP System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Level")
	int32 CurrentLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Level")
	int32 CurrentXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Level")
	int32 MaxXPForCurrentLevel;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Level")
	void AddXP(int32 Amount, FString Reason);

	/** Rank System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Rank")
	EBlackoutCompetitiveRank CompetitiveRank;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Rank")
	int32 RankPoints;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Rank")
	void AddRankPoints(int32 DeltaPoints);

	/** Statistics & Missions */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Stats")
	FBlackoutPlayerStats LifetimeStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Missions")
	TArray<FBlackoutDailyMission> ActiveDailyMissions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Achievements")
	TArray<FBlackoutAchievement> Achievements;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Stats")
	void UpdateStatsOnMatchEnd(const FBlackoutPlayerStats& MatchStats);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Missions")
	void GenerateDailyMissions();
};
