#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackoutLiveOpsManager.generated.h"

USTRUCT(BlueprintType)
struct FBlackoutLiveEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | LiveOps")
	FString EventID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | LiveOps")
	FString EventName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | LiveOps")
	float DoubleXPXMultiplier = 1.0f;
};

UCLASS()
class PROJECTBLACKOUT_API UBlackoutLiveOpsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutLiveOpsSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Maintenance")
	bool bMaintenanceModeActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Maintenance")
	FString MaintenanceMessage;

	UFUNCTION(BlueprintCallable, Category = "Blackout | LiveOps")
	bool CheckMaintenanceStatus();

	UFUNCTION(BlueprintCallable, Category = "Blackout | LiveOps")
	bool ValidateClientVersion(FString ClientVersion);

	UFUNCTION(BlueprintCallable, Category = "Blackout | LiveOps")
	bool CheckForHotfixes(FString CurrentVersion, FString& OutPatchNotes);

	UFUNCTION(BlueprintCallable, Category = "Blackout | LiveOps")
	TArray<FBlackoutLiveEvent> GetActiveLiveEvents();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Telemetry")
	void LogCrashTelemetry(FString CrashCallstack);
};
