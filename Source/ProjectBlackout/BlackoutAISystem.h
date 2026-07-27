#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BlackoutCharacter.h"
#include "BlackoutAISystem.generated.h"

UENUM(BlueprintType)
enum class EBlackoutAIDifficulty : uint8
{
	Easy     UMETA(DisplayName = "Easy"),
	Normal   UMETA(DisplayName = "Normal"),
	Hard     UMETA(DisplayName = "Hard"),
	Expert   UMETA(DisplayName = "Expert")
};

UENUM(BlueprintType)
enum class EBlackoutAIState : uint8
{
	Patrol       UMETA(DisplayName = "Patrol"),
	Investigate  UMETA(DisplayName = "Investigate"),
	Chase        UMETA(DisplayName = "Chase"),
	Combat       UMETA(DisplayName = "Combat"),
	TakeCover    UMETA(DisplayName = "Take Cover"),
	Retreat      UMETA(DisplayName = "Retreat"),
	Flank        UMETA(DisplayName = "Flank")
};

/** AI Character Pawn */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutAICharacter : public ABlackoutCharacter
{
	GENERATED_BODY()

public:
	ABlackoutAICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | AI")
	EBlackoutAIDifficulty Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | AI Squad")
	int32 SquadID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | AI Squad")
	bool bIsSquadLeader;
};

/** AI Controller */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABlackoutAIController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Perception")
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Perception")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Perception")
	UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | AI State")
	EBlackoutAIState CurrentAIState;

	UFUNCTION(BlueprintCallable, Category = "Blackout | AI State")
	void SetAIState(EBlackoutAIState NewState);

	UFUNCTION(BlueprintCallable, Category = "Blackout | AI Perception")
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable, Category = "Blackout | AI Actions")
	void FindCoverLocation();

	UFUNCTION(BlueprintCallable, Category = "Blackout | AI Actions")
	void ApplyDifficultyParameters(EBlackoutAIDifficulty Difficulty);
};
