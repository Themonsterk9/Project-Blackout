#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackoutProgressionSystem.h"
#include "BlackoutBackendService.generated.h"

USTRUCT(BlueprintType)
struct FBlackoutLeaderboardEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Leaderboard")
	int32 RankPosition = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Leaderboard")
	FString Username = TEXT("Player");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Leaderboard")
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Leaderboard")
	int32 Kills = 0;
};

UCLASS()
class PROJECTBLACKOUT_API UBlackoutBackendService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutBackendService();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Authentication */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Auth")
	FString AuthToken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Auth")
	bool bIsAuthenticated;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Backend Auth")
	bool RegisterUser(FString Username, FString Password);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Backend Auth")
	bool LoginUser(FString Username, FString Password);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Backend Auth")
	bool ValidateAuthToken(FString Token);

	/** Cloud Save & Data Sync */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Cloud Save")
	bool SyncPlayerDataToCloud();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Cloud Save")
	bool FetchPlayerDataFromCloud();

	/** Leaderboards */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Leaderboards")
	TArray<FBlackoutLeaderboardEntry> GetGlobalLeaderboard();

	/** Match History */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Match History")
	void LogMatchResult(FString MatchID, const FBlackoutPlayerStats& Stats);

	/** Security Helper */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Backend Security")
	FString HashPayload(FString PayloadData) const;
};
