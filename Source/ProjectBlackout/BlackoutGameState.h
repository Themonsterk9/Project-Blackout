#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "BlackoutGameState.generated.h"

UCLASS()
class PROJECTBLACKOUT_API ABlackoutGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ABlackoutGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | State")
	int32 TeamAScore;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | State")
	int32 TeamBScore;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | State")
	float RemainingMatchTime;
};
