#pragma once

#include "CoreMinimal.h"
#include "BlackoutCharacterState.generated.h"

/**
 * All 13 core character locomotion and movement states for Project Blackout.
 */
UENUM(BlueprintType)
enum class EBlackoutCharacterState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Walking     UMETA(DisplayName = "Walking"),
	Running     UMETA(DisplayName = "Running"),
	Sprinting   UMETA(DisplayName = "Sprinting"),
	Jumping     UMETA(DisplayName = "Jumping"),
	Falling     UMETA(DisplayName = "Falling"),
	Landing     UMETA(DisplayName = "Landing"),
	Crouching   UMETA(DisplayName = "Crouching"),
	Prone       UMETA(DisplayName = "Prone"),
	Crawling    UMETA(DisplayName = "Crawling"),
	Sliding     UMETA(DisplayName = "Sliding"),
	Climbing    UMETA(DisplayName = "Climbing"),
	Vaulting    UMETA(DisplayName = "Vaulting")
};

/**
 * Configurable movement parameters and capsule dimensions for character states.
 */
USTRUCT(BlueprintType)
struct FBlackoutMovementConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float WalkSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float RunSpeed = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float SprintSpeed = 650.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float CrouchSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float ProneSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float SlideSpeed = 750.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Speeds")
	float ClimbSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Dimensions")
	float StandingCapsuleHalfHeight = 88.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Dimensions")
	float CrouchingCapsuleHalfHeight = 55.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Dimensions")
	float ProneCapsuleHalfHeight = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Architecture")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Architecture")
	float SprintStaminaDrainRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Detection")
	float VaultMaxHeight = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Detection")
	float ClimbMaxHeight = 250.0f;
};
