#include "BlackoutMapFramework.h"

ABlackoutSpawnPoint::ABlackoutSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	TeamID = 0;
	bIsOccupied = false;
}

ABlackoutEnvironmentSystem::ABlackoutEnvironmentSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	TimeOfDayHours = 12.0f;
	bAnimateDayNightCycle = true;
	CurrentWeather = EBlackoutWeatherType::Clear;
}

void ABlackoutEnvironmentSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAnimateDayNightCycle)
	{
		TimeOfDayHours += DeltaTime * 0.05f;
		if (TimeOfDayHours >= 24.0f)
		{
			TimeOfDayHours -= 24.0f;
		}
	}
}

void ABlackoutEnvironmentSystem::SetWeather(EBlackoutWeatherType NewWeather)
{
	CurrentWeather = NewWeather;
}
