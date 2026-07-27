#include "BlackoutProgressionSystem.h"

UBlackoutProgressionSubsystem::UBlackoutProgressionSubsystem()
{
	CurrentLevel = 1;
	CurrentXP = 0;
	MaxXPForCurrentLevel = 1000;
	CompetitiveRank = EBlackoutCompetitiveRank::Bronze;
	RankPoints = 0;
}

void UBlackoutProgressionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GenerateDailyMissions();
}

void UBlackoutProgressionSubsystem::AddXP(int32 Amount, FString Reason)
{
	if (Amount <= 0) return;

	CurrentXP += Amount;
	while (CurrentXP >= MaxXPForCurrentLevel && CurrentLevel < 100)
	{
		CurrentXP -= MaxXPForCurrentLevel;
		CurrentLevel++;
		MaxXPForCurrentLevel = 1000 + (CurrentLevel * 250);
	}
}

void UBlackoutProgressionSubsystem::AddRankPoints(int32 DeltaPoints)
{
	RankPoints = FMath::Max(0, RankPoints + DeltaPoints);

	if (RankPoints < 500) CompetitiveRank = EBlackoutCompetitiveRank::Bronze;
	else if (RankPoints < 1200) CompetitiveRank = EBlackoutCompetitiveRank::Silver;
	else if (RankPoints < 2500) CompetitiveRank = EBlackoutCompetitiveRank::Gold;
	else if (RankPoints < 4500) CompetitiveRank = EBlackoutCompetitiveRank::Platinum;
	else if (RankPoints < 7000) CompetitiveRank = EBlackoutCompetitiveRank::Diamond;
	else if (RankPoints < 10000) CompetitiveRank = EBlackoutCompetitiveRank::Master;
	else CompetitiveRank = EBlackoutCompetitiveRank::Grandmaster;
}

void UBlackoutProgressionSubsystem::UpdateStatsOnMatchEnd(const FBlackoutPlayerStats& MatchStats)
{
	LifetimeStats.MatchesPlayed += MatchStats.MatchesPlayed;
	LifetimeStats.Wins += MatchStats.Wins;
	LifetimeStats.Losses += MatchStats.Losses;
	LifetimeStats.Kills += MatchStats.Kills;
	LifetimeStats.Deaths += MatchStats.Deaths;
	LifetimeStats.Assists += MatchStats.Assists;
	LifetimeStats.Headshots += MatchStats.Headshots;
	LifetimeStats.TimePlayedSeconds += MatchStats.TimePlayedSeconds;
	LifetimeStats.DistanceTraveledMeters += MatchStats.DistanceTraveledMeters;
	LifetimeStats.RevivesCount += MatchStats.RevivesCount;

	if (LifetimeStats.Kills > 0 && LifetimeStats.Deaths > 0)
	{
		// Stats updated
	}
}

void UBlackoutProgressionSubsystem::GenerateDailyMissions()
{
	ActiveDailyMissions.Empty();

	FBlackoutDailyMission M1;
	M1.MissionID = TEXT("Daily_Elims");
	M1.Description = TEXT("Eliminate 10 opponents in any game mode");
	M1.TargetProgress = 10;
	M1.RewardXP = 500;
	ActiveDailyMissions.Add(M1);

	FBlackoutDailyMission M2;
	M2.MissionID = TEXT("Daily_Headshots");
	M2.Description = TEXT("Score 5 Headshot eliminations");
	M2.TargetProgress = 5;
	M2.RewardXP = 750;
	ActiveDailyMissions.Add(M2);
}
