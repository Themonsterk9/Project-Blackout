#include "BlackoutGameModes.h"
#include "BlackoutGameState.h"
#include "Engine/World.h"

ABlackoutCaptureZone::ABlackoutCaptureZone()
{
	PrimaryActorTick.bCanEverTick = false;
	ZoneName = TEXT("Alpha");
	ControllingTeamID = -1;
	CaptureProgress = 0.0f;
}

void ABlackoutCaptureZone::UpdateCapture(int32 TeamID, float DeltaProgress)
{
	if (ControllingTeamID == TeamID)
	{
		CaptureProgress = FMath::Clamp(CaptureProgress + DeltaProgress, 0.0f, 100.0f);
	}
	else
	{
		CaptureProgress -= DeltaProgress;
		if (CaptureProgress <= 0.0f)
		{
			ControllingTeamID = TeamID;
			CaptureProgress = 0.0f;
		}
	}
}

ABlackoutGameMode_TDM::ABlackoutGameMode_TDM()
{
	TargetKillsToWin = 50;
}

void ABlackoutGameMode_TDM::AddKillScore(int32 ScoringTeamID)
{
	ABlackoutGameState* GS = GetGameState<ABlackoutGameState>();
	if (GS)
	{
		if (ScoringTeamID == 1)
		{
			GS->TeamAScore++;
		}
		else if (ScoringTeamID == 2)
		{
			GS->TeamBScore++;
		}
	}
}

ABlackoutGameMode_FFA::ABlackoutGameMode_FFA()
{
	ScoreLimitToWin = 30;
}

ABlackoutGameMode_Domination::ABlackoutGameMode_Domination()
{
	TargetPointsToWin = 200;
}

ABlackoutGameMode_SnD::ABlackoutGameMode_SnD()
{
	BombPlantDuration = 5.0f;
	BombDefuseDuration = 7.0f;
	RoundTimeSeconds = 120.0f;
	bIsBombPlanted = false;
}

ABlackoutGameMode_BattleRoyale::ABlackoutGameMode_BattleRoyale()
{
	SafeZoneRadius = 50000.0f;
	ShrinkSpeed = 100.0f;
	AlivePlayersCount = 100;
}

void ABlackoutGameMode_BattleRoyale::OnPlayerEliminated(AController* EliminatedController)
{
	AlivePlayersCount = FMath::Max(0, AlivePlayersCount - 1);
}

ABlackoutGameMode_Practice::ABlackoutGameMode_Practice()
{
	BotCountToSpawn = 10;
}

void ABlackoutGameMode_Practice::SpawnPracticeBots()
{
}
