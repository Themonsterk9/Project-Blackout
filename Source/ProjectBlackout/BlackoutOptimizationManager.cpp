#include "BlackoutOptimizationManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UBlackoutObjectPoolSubsystem::UBlackoutObjectPoolSubsystem()
{
}

void UBlackoutObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

AActor* UBlackoutObjectPoolSubsystem::GetPooledActor(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation)
{
	if (!ActorClass) return nullptr;

	UClass* KeyClass = ActorClass.Get();
	if (InactivePool.Contains(KeyClass) && InactivePool[KeyClass].Num() > 0)
	{
		AActor* PooledActor = InactivePool[KeyClass].Pop();
		if (PooledActor && IsValid(PooledActor))
		{
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
			PooledActor->SetActorHiddenInGame(false);
			PooledActor->SetActorEnableCollision(true);
			PooledActor->SetActorTickEnabled(true);
			return PooledActor;
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<AActor>(ActorClass, Location, Rotation, SpawnParams);
}

void UBlackoutObjectPoolSubsystem::ReturnPooledActor(AActor* ActorToReturn)
{
	if (!ActorToReturn || !IsValid(ActorToReturn)) return;

	ActorToReturn->SetActorHiddenInGame(true);
	ActorToReturn->SetActorEnableCollision(false);
	ActorToReturn->SetActorTickEnabled(false);

	UClass* KeyClass = ActorToReturn->GetClass();
	InactivePool.FindOrAdd(KeyClass).Add(ActorToReturn);
}

UBlackoutPerformanceSubsystem::UBlackoutPerformanceSubsystem()
{
}

void UBlackoutPerformanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ConfigurePlatformOptimizations();
}

void UBlackoutPerformanceSubsystem::ApplyQualityPreset(FString PresetName)
{
	if (PresetName.Equals(TEXT("Low"), ESearchCase::IgnoreCase))
	{
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.ShadowQuality 0"));
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.PostProcessingQuality 0"));
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.TextureStreaming 1"));
	}
	else if (PresetName.Equals(TEXT("Ultra"), ESearchCase::IgnoreCase))
	{
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.ShadowQuality 5"));
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.PostProcessingQuality 5"));
		UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.Nanite 1"));
	}
}

void UBlackoutPerformanceSubsystem::ConfigurePlatformOptimizations()
{
#if PLATFORM_ANDROID
	UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.MobileHDR 1"));
	UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.MobileContentScaleFactor 0.85"));
#elif PLATFORM_IOS
	UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.Metal.EnableWaveIntrinsics 1"));
#else
	UGameplayStatics::ExecuteConsoleCommand(GetWorld(), TEXT("r.MaxFPS 144"));
#endif
}

void UBlackoutPerformanceSubsystem::OptimizeNetworkReplication(AActor* TargetActor)
{
	if (TargetActor)
	{
		TargetActor->SetNetDormancy(DORM_DormantAll);
		TargetActor->NetUpdateFrequency = 20.0f;
		TargetActor->NetCullDistanceSquared = 400000000.0f;
	}
}

void UBlackoutPerformanceSubsystem::AsyncPreloadLevel(FString MapName)
{
}
