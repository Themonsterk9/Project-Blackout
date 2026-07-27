#include "BlackoutGameMode.h"
#include "BlackoutGameState.h"
#include "BlackoutPlayerState.h"
#include "BlackoutCharacter.h"
#include "BlackoutPlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

ABlackoutGameMode::ABlackoutGameMode()
{
	DefaultPawnClass = ABlackoutCharacter::StaticClass();
	PlayerControllerClass = ABlackoutPlayerController::StaticClass();
	GameStateClass = ABlackoutGameState::StaticClass();
	PlayerStateClass = ABlackoutPlayerState::StaticClass();

	MaxPlayersPerMatch = 64;
	RespawnDelaySeconds = 3.0f;
}

void ABlackoutGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ABlackoutGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void ABlackoutGameMode::RespawnPlayer(AController* Controller)
{
	if (Controller)
	{
		GetWorldTimerManager().SetTimerForNextTick([this, Controller]()
		{
			AActor* SpawnPoint = FindPlayerStart(Controller);
			APawn* NewPawn = SpawnDefaultPawnFor(Controller, SpawnPoint);
			if (NewPawn)
			{
				Controller->Possess(NewPawn);
			}
		});
	}
}
