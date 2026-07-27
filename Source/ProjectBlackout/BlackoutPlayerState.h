#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "BlackoutPlayerState.generated.h"

UCLASS()
class PROJECTBLACKOUT_API ABlackoutPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ABlackoutPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Player Stats")
	int32 Kills;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Player Stats")
	int32 Deaths;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Player Stats")
	int32 Assists;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Player Stats")
	int32 TeamID;
};
