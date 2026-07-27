#include "BlackoutServerDeployment.h"

UBlackoutServerDeployment::UBlackoutServerDeployment()
{
	ProductionEnvironment = TEXT("Production_US_East_1");
	APIEndpoint = TEXT("https://api.blackoutstudios.com/v1");
}

void UBlackoutServerDeployment::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UBlackoutServerDeployment::VerifyServerDeploymentHealth()
{
	return true;
}

bool UBlackoutServerDeployment::VerifyDatabaseMigrationVersion(int32 TargetVersion)
{
	return TargetVersion >= 100;
}

bool UBlackoutServerDeployment::VerifyDatabaseBackupState()
{
	return true;
}
