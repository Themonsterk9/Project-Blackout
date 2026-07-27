#include "BlackoutCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ABlackoutCharacter::ABlackoutCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set capsule size
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	// Configure character movement
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->bCanWalkOffLedgesWhenCrouching = true;
		MoveComp->MaxWalkSpeed = MovementConfig.RunSpeed;
		MoveComp->MaxWalkSpeedCrouched = MovementConfig.CrouchSpeed;
		MoveComp->JumpZVelocity = 600.0f;
		MoveComp->AirControl = 0.35f;
		MoveComp->MaxStepHeight = 45.0f;
		MoveComp->SetWalkableFloorAngle(45.0f);
		MoveComp->BrakingDecelerationWalking = 2048.0f;
		MoveComp->GroundFriction = 8.0f;
		MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	CurrentState = EBlackoutCharacterState::Idle;
	SlideDurationTimer = 0.0f;
	SlideDirection = FVector::ZeroVector;
}

void ABlackoutCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterState(EBlackoutCharacterState::Idle);
}

void ABlackoutCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update movement state based on current velocity if grounded
	if (GetCharacterMovement()->IsFalling())
	{
		if (CurrentState != EBlackoutCharacterState::Jumping && CurrentState != EBlackoutCharacterState::Vaulting && CurrentState != EBlackoutCharacterState::Climbing)
		{
			SetCharacterState(EBlackoutCharacterState::Falling);
		}
	}
	else if (CurrentState == EBlackoutCharacterState::Sliding)
	{
		UpdateSlide(DeltaTime);
	}
	else if (CurrentState != EBlackoutCharacterState::Crouching && CurrentState != EBlackoutCharacterState::Prone && CurrentState != EBlackoutCharacterState::Crawling && CurrentState != EBlackoutCharacterState::Climbing && CurrentState != EBlackoutCharacterState::Vaulting)
	{
		const float CurrentSpeed = GetVelocity().Size2D();
		if (CurrentSpeed <= 10.0f)
		{
			SetCharacterState(EBlackoutCharacterState::Idle);
		}
		else if (CurrentSpeed <= MovementConfig.WalkSpeed + 20.0f)
		{
			SetCharacterState(EBlackoutCharacterState::Walking);
		}
		else if (CurrentSpeed <= MovementConfig.RunSpeed + 20.0f)
		{
			SetCharacterState(EBlackoutCharacterState::Running);
		}
		else
		{
			SetCharacterState(EBlackoutCharacterState::Sprinting);
		}
	}
}

void ABlackoutCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABlackoutCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlackoutCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABlackoutCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ABlackoutCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABlackoutCharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABlackoutCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABlackoutCharacter::StopSprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABlackoutCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABlackoutCharacter::StopCrouch);
	PlayerInputComponent->BindAction("Prone", IE_Pressed, this, &ABlackoutCharacter::ToggleProne);
	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &ABlackoutCharacter::StartSlide);
	PlayerInputComponent->BindAction("Vault", IE_Pressed, this, &ABlackoutCharacter::TryVault);
	PlayerInputComponent->BindAction("Climb", IE_Pressed, this, &ABlackoutCharacter::TryClimb);
}

bool ABlackoutCharacter::CanTransitionToState(EBlackoutCharacterState NewState) const
{
	// Disallow jumping or sprinting from Prone or Climbing without exiting first
	if (CurrentState == EBlackoutCharacterState::Prone || CurrentState == EBlackoutCharacterState::Crawling)
	{
		if (NewState == EBlackoutCharacterState::Jumping || NewState == EBlackoutCharacterState::Sprinting || NewState == EBlackoutCharacterState::Sliding)
		{
			return false;
		}
	}

	if (CurrentState == EBlackoutCharacterState::Climbing && NewState == EBlackoutCharacterState::Sliding)
	{
		return false;
	}

	return true;
}

bool ABlackoutCharacter::SetCharacterState(EBlackoutCharacterState NewState)
{
	if (!CanTransitionToState(NewState))
	{
		return false;
	}

	CurrentState = NewState;
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	switch (CurrentState)
	{
	case EBlackoutCharacterState::Idle:
	case EBlackoutCharacterState::Walking:
		MoveComp->MaxWalkSpeed = MovementConfig.WalkSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.StandingCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Running:
		MoveComp->MaxWalkSpeed = MovementConfig.RunSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.StandingCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Sprinting:
		MoveComp->MaxWalkSpeed = MovementConfig.SprintSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.StandingCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Crouching:
		MoveComp->MaxWalkSpeed = MovementConfig.CrouchSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.CrouchingCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Prone:
	case EBlackoutCharacterState::Crawling:
		MoveComp->MaxWalkSpeed = MovementConfig.ProneSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.ProneCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Sliding:
		MoveComp->MaxWalkSpeed = MovementConfig.SlideSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.CrouchingCapsuleHalfHeight);
		break;
	case EBlackoutCharacterState::Climbing:
		MoveComp->MaxWalkSpeed = MovementConfig.ClimbSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(MovementConfig.StandingCapsuleHalfHeight);
		break;
	default:
		break;
	}

	return true;
}

void ABlackoutCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABlackoutCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABlackoutCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate);
}

void ABlackoutCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate);
}

void ABlackoutCharacter::StartSprint()
{
	if (CurrentState != EBlackoutCharacterState::Crouching && CurrentState != EBlackoutCharacterState::Prone)
	{
		SetCharacterState(EBlackoutCharacterState::Sprinting);
	}
}

void ABlackoutCharacter::StopSprint()
{
	if (CurrentState == EBlackoutCharacterState::Sprinting)
	{
		SetCharacterState(EBlackoutCharacterState::Running);
	}
}

void ABlackoutCharacter::StartCrouch()
{
	SetCharacterState(EBlackoutCharacterState::Crouching);
}

void ABlackoutCharacter::StopCrouch()
{
	if (CurrentState == EBlackoutCharacterState::Crouching)
	{
		SetCharacterState(EBlackoutCharacterState::StandingCapsuleHalfHeight > 0 ? EBlackoutCharacterState::Running : EBlackoutCharacterState::Walking);
	}
}

void ABlackoutCharacter::ToggleProne()
{
	if (CurrentState == EBlackoutCharacterState::Prone || CurrentState == EBlackoutCharacterState::Crawling)
	{
		SetCharacterState(EBlackoutCharacterState::Idle);
	}
	else
	{
		SetCharacterState(EBlackoutCharacterState::Prone);
	}
}

void ABlackoutCharacter::StartSlide()
{
	if (CurrentState == EBlackoutCharacterState::Sprinting)
	{
		SetCharacterState(EBlackoutCharacterState::Sliding);
		SlideDurationTimer = 1.2f;
		SlideDirection = GetActorForwardVector();
		LaunchCharacter(SlideDirection * 400.0f, false, false);
	}
}

void ABlackoutCharacter::UpdateSlide(float DeltaTime)
{
	SlideDurationTimer -= DeltaTime;
	if (SlideDurationTimer <= 0.0f || GetVelocity().Size2D() < 200.0f)
	{
		SetCharacterState(EBlackoutCharacterState::Crouching);
	}
}

void ABlackoutCharacter::TryVault()
{
	FHitResult LowHit;
	if (TraceObstacle(120.0f, -40.0f, LowHit))
	{
		FHitResult HighHit;
		if (!TraceObstacle(120.0f, 40.0f, HighHit))
		{
			// Low obstacle detected, perform vault
			SetCharacterState(EBlackoutCharacterState::Vaulting);
			LaunchCharacter(FVector(0, 0, 450.0f) + GetActorForwardVector() * 300.0f, true, true);
		}
	}
}

void ABlackoutCharacter::TryClimb()
{
	FHitResult WallHit;
	if (TraceObstacle(100.0f, 20.0f, WallHit))
	{
		SetCharacterState(EBlackoutCharacterState::Climbing);
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		LaunchCharacter(FVector(0, 0, 350.0f), true, true);
	}
}

bool ABlackoutCharacter::TraceObstacle(float TraceDistance, float EyeHeightOffset, FHitResult& OutHit) const
{
	const FVector Start = GetActorLocation() + FVector(0, 0, EyeHeightOffset);
	const FVector End = Start + GetActorForwardVector() * TraceDistance;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, QueryParams);
}

void ABlackoutCharacter::Jump()
{
	if (CurrentState != EBlackoutCharacterState::Prone && CurrentState != EBlackoutCharacterState::Crawling && CurrentState != EBlackoutCharacterState::Sliding)
	{
		SetCharacterState(EBlackoutCharacterState::Jumping);
		Super::Jump();
	}
}

void ABlackoutCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	SetCharacterState(EBlackoutCharacterState::Landing);
}
