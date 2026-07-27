#include "BlackoutGameState.h"

ABlackoutGameState::ABlackoutGameState()
{
	TeamAScore = 0;
	TeamBScore = 0;
	RemainingMatchTime = 600.0f;
}

void ABlackoutGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlackoutGameState, TeamAScore);
	DOREPLIFETIME(ABlackoutGameState, TeamBScore);
	DOREPLIFETIME(ABlackoutGameState, RemainingMatchTime);
}
