#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlackoutGameMode.generated.h"

UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlackoutGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Rules")
	int32 MaxPlayersPerMatch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Rules")
	float RespawnDelaySeconds;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Rules")
	void RespawnPlayer(AController* Controller);
};
