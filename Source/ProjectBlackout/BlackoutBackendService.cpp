#include "BlackoutBackendService.h"
#include "Misc/SecureHash.h"

UBlackoutBackendService::UBlackoutBackendService()
{
	AuthToken = TEXT("");
	bIsAuthenticated = false;
}

void UBlackoutBackendService::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UBlackoutBackendService::RegisterUser(FString Username, FString Password)
{
	if (!Username.IsEmpty() && !Password.IsEmpty())
	{
		AuthToken = FMD5::HashAnsiString(*(Username + Password + TEXT("SaltKey2026")));
		bIsAuthenticated = true;
		return true;
	}
	return false;
}

bool UBlackoutBackendService::LoginUser(FString Username, FString Password)
{
	return RegisterUser(Username, Password);
}

bool UBlackoutBackendService::ValidateAuthToken(FString Token)
{
	return !Token.IsEmpty() && Token == AuthToken;
}

bool UBlackoutBackendService::SyncPlayerDataToCloud()
{
	return bIsAuthenticated;
}

bool UBlackoutBackendService::FetchPlayerDataFromCloud()
{
	return bIsAuthenticated;
}

TArray<FBlackoutLeaderboardEntry> UBlackoutBackendService::GetGlobalLeaderboard()
{
	TArray<FBlackoutLeaderboardEntry> Board;
	for (int32 i = 1; i <= 10; ++i)
	{
		FBlackoutLeaderboardEntry Entry;
		Entry.RankPosition = i;
		Entry.Username = FString::Printf(TEXT("ProOperator_%d"), i);
		Entry.Score = 50000 - (i * 2500);
		Entry.Kills = 500 - (i * 30);
		Board.Add(Entry);
	}
	return Board;
}

void UBlackoutBackendService::LogMatchResult(FString MatchID, const FBlackoutPlayerStats& Stats)
{
}

FString UBlackoutBackendService::HashPayload(FString PayloadData) const
{
	return FMD5::HashAnsiString(*PayloadData);
}
