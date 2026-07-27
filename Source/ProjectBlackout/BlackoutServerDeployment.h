#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackoutServerDeployment.generated.h"

UCLASS()
class PROJECTBLACKOUT_API UBlackoutServerDeployment : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutServerDeployment();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Deployment")
	FString ProductionEnvironment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Deployment")
	FString APIEndpoint;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Deployment")
	bool VerifyServerDeploymentHealth();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Deployment")
	bool VerifyDatabaseMigrationVersion(int32 TargetVersion);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Deployment")
	bool VerifyDatabaseBackupState();
};
