#include "BlackoutLiveOpsManager.h"

UBlackoutLiveOpsSubsystem::UBlackoutLiveOpsSubsystem()
{
	bMaintenanceModeActive = false;
	MaintenanceMessage = TEXT("Servers are operating normally.");
}

void UBlackoutLiveOpsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UBlackoutLiveOpsSubsystem::CheckMaintenanceStatus()
{
	return bMaintenanceModeActive;
}

bool UBlackoutLiveOpsSubsystem::ValidateClientVersion(FString ClientVersion)
{
	return ClientVersion.Equals(TEXT("1.0.0"), ESearchCase::IgnoreCase);
}

bool UBlackoutLiveOpsSubsystem::CheckForHotfixes(FString CurrentVersion, FString& OutPatchNotes)
{
	if (CurrentVersion.Equals(TEXT("1.0.0")))
	{
		OutPatchNotes = TEXT("Client is up to date (v1.0.0 Production Release).");
		return false;
	}
	OutPatchNotes = TEXT("Hotfix v1.0.0 Available.");
	return true;
}

TArray<FBlackoutLiveEvent> UBlackoutLiveOpsSubsystem::GetActiveLiveEvents()
{
	TArray<FBlackoutLiveEvent> Events;
	FBlackoutLiveEvent E1;
	E1.EventID = TEXT("Season1_Launch");
	E1.EventName = TEXT("Season 1: Operation Blackout");
	E1.DoubleXPXMultiplier = 2.0f;
	Events.Add(E1);
	return Events;
}

void UBlackoutLiveOpsSubsystem::LogCrashTelemetry(FString CrashCallstack)
{
}
