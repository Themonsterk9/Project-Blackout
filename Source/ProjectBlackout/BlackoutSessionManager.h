#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackoutSessionManager.generated.h"

UCLASS()
class PROJECTBLACKOUT_API UBlackoutSessionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutSessionManager();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Session Methods */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Session")
	bool CreateLobby(int32 MaxPlayers, bool bIsLAN);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Session")
	bool JoinLobby(FString SessionID);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Session")
	void LeaveLobby();

	/** Matchmaking Hooks */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Matchmaking")
	void StartQuickMatch();

	/** Party & Friends Hooks */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Social")
	void SendPartyInvite(FString FriendUserID);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Voice")
	void ToggleMuteTeamVoice(bool bMute);
};
