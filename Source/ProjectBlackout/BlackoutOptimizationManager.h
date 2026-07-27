#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/Actor.h"
#include "BlackoutOptimizationManager.generated.h"

/** Object Pooling Subsystem for Zero-Allocation Spawning */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutObjectPoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutObjectPoolSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Object Pool")
	AActor* GetPooledActor(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Object Pool")
	void ReturnPooledActor(AActor* ActorToReturn);

private:
	UPROPERTY()
	TMap<UClass*, TArray<AActor*>> InactivePool;
};

/** Performance & Platform Optimization Subsystem */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutPerformanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutPerformanceSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Graphics Presets */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Optimization")
	void ApplyQualityPreset(FString PresetName);

	/** Platform Optimization */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Platform Optimization")
	void ConfigurePlatformOptimizations();

	/** Network Optimization */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Network Optimization")
	void OptimizeNetworkReplication(AActor* TargetActor);

	/** Level Preloading */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Loading Optimization")
	void AsyncPreloadLevel(FString MapName);
};
