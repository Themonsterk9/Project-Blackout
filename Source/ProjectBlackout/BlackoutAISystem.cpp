#include "BlackoutAISystem.h"
#include "Perception/AIPerceptionSystem.h"

ABlackoutAICharacter::ABlackoutAICharacter()
{
	Difficulty = EBlackoutAIDifficulty::Normal;
	SquadID = 1;
	bIsSquadLeader = false;
}

ABlackoutAIController::ABlackoutAIController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 3000.0f;
	SightConfig->LoseSightRadius = 3500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 2000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;

	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->ConfigureSense(*HearingConfig);
	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	CurrentAIState = EBlackoutAIState::Patrol;
}

void ABlackoutAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerceptionComp)
	{
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ABlackoutAIController::OnTargetPerceived);
	}
}

void ABlackoutAIController::SetAIState(EBlackoutAIState NewState)
{
	CurrentAIState = NewState;
}

void ABlackoutAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		SetAIState(EBlackoutAIState::Combat);
	}
	else
	{
		SetAIState(EBlackoutAIState::Investigate);
	}
}

void ABlackoutAIController::FindCoverLocation()
{
	SetAIState(EBlackoutAIState::TakeCover);
}

void ABlackoutAIController::ApplyDifficultyParameters(EBlackoutAIDifficulty Difficulty)
{
	switch (Difficulty)
	{
	case EBlackoutAIDifficulty::Easy:
		SightConfig->SightRadius = 2000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 60.0f;
		break;
	case EBlackoutAIDifficulty::Normal:
		SightConfig->SightRadius = 3000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		break;
	case EBlackoutAIDifficulty::Hard:
		SightConfig->SightRadius = 4000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 120.0f;
		break;
	case EBlackoutAIDifficulty::Expert:
		SightConfig->SightRadius = 5500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 160.0f;
		break;
	}
}
