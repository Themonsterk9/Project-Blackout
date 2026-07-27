#include "BlackoutPlayerState.h"

ABlackoutPlayerState::ABlackoutPlayerState()
{
	Kills = 0;
	Deaths = 0;
	Assists = 0;
	TeamID = 0;
}

void ABlackoutPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlackoutPlayerState, Kills);
	DOREPLIFETIME(ABlackoutPlayerState, Deaths);
	DOREPLIFETIME(ABlackoutPlayerState, Assists);
	DOREPLIFETIME(ABlackoutPlayerState, TeamID);
}
