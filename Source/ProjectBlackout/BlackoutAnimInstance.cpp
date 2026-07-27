#include "BlackoutAnimInstance.h"
#include "BlackoutCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetAnimationLibrary.h"

UBlackoutAnimInstance::UBlackoutAnimInstance()
{
	Speed = 0.0f;
	Direction = 0.0f;
	bIsInAir = false;
	bIsCrouching = false;
	bIsProne = false;
	bIsSliding = false;
	bIsClimbing = false;
	bIsVaulting = false;
	CharacterState = EBlackoutCharacterState::Idle;
	CharacterOwner = nullptr;
}

void UBlackoutAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CharacterOwner = Cast<ABlackoutCharacter>(TryGetPawnOwner());
}

void UBlackoutAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!CharacterOwner)
	{
		CharacterOwner = Cast<ABlackoutCharacter>(TryGetPawnOwner());
	}

	if (CharacterOwner)
	{
		const FVector Velocity = CharacterOwner->GetVelocity();
		Speed = Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, CharacterOwner->GetActorRotation());

		UCharacterMovementComponent* MoveComp = CharacterOwner->GetCharacterMovement();
		if (MoveComp)
		{
			bIsInAir = MoveComp->IsFalling();
		}

		CharacterState = CharacterOwner->CurrentState;
		bIsCrouching = (CharacterState == EBlackoutCharacterState::Crouching);
		bIsProne = (CharacterState == EBlackoutCharacterState::Prone || CharacterState == EBlackoutCharacterState::Crawling);
		bIsSliding = (CharacterState == EBlackoutCharacterState::Sliding);
		bIsClimbing = (CharacterState == EBlackoutCharacterState::Climbing);
		bIsVaulting = (CharacterState == EBlackoutCharacterState::Vaulting);
	}
}
