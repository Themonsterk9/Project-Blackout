#include "BlackoutSessionManager.h"

UBlackoutSessionManager::UBlackoutSessionManager()
{
}

void UBlackoutSessionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UBlackoutSessionManager::CreateLobby(int32 MaxPlayers, bool bIsLAN)
{
	return true;
}

bool UBlackoutSessionManager::JoinLobby(FString SessionID)
{
	return true;
}

void UBlackoutSessionManager::LeaveLobby()
{
}

void UBlackoutSessionManager::StartQuickMatch()
{
}

void UBlackoutSessionManager::SendPartyInvite(FString FriendUserID)
{
}

void UBlackoutSessionManager::ToggleMuteTeamVoice(bool bMute)
{
}
