#include "BlackoutCameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UBlackoutCameraComponent::UBlackoutCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentPerspective = EBlackoutPerspective::FirstPerson;
	FPP_FOV = 90.0f;
	TPP_FOV = 80.0f;
	ADS_FOV = 70.0f;
	TargetFOV = FPP_FOV;

	MouseSensitivity = 1.0f;
	ControllerSensitivity = 1.0f;
	TouchSensitivity = 1.0f;
	bInvertY = false;

	HeadBobTimer = 0.0f;
	SpringArmRef = nullptr;
}

void UBlackoutCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	SetPerspective(CurrentPerspective);
}

void UBlackoutCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Smooth FOV Interpolation
	if (!FMath::IsNearlyEqual(FieldOfView, TargetFOV, 0.1f))
	{
		SetFieldOfView(FMath::FInterpTo(FieldOfView, TargetFOV, DeltaTime, 12.0f));
	}

	// Process procedural head bob in FPP mode
	AActor* Owner = GetOwner();
	if (Owner && CurrentPerspective == EBlackoutPerspective::FirstPerson)
	{
		const float Speed = Owner->GetVelocity().Size2D();
		UpdateHeadBob(Speed, DeltaTime);
	}
}

void UBlackoutCameraComponent::SetPerspective(EBlackoutPerspective NewPerspective)
{
	CurrentPerspective = NewPerspective;

	if (SpringArmRef)
	{
		switch (CurrentPerspective)
		{
		case EBlackoutPerspective::FirstPerson:
			SpringArmRef->TargetArmLength = 0.0f;
			SpringArmRef->SocketOffset = FVector(0.0f, 0.0f, 60.0f);
			SpringArmRef->bDoCollisionTest = false;
			TargetFOV = FPP_FOV;
			break;
		case EBlackoutPerspective::ThirdPersonRight:
			SpringArmRef->TargetArmLength = 250.0f;
			SpringArmRef->SocketOffset = FVector(0.0f, 45.0f, 50.0f);
			SpringArmRef->bDoCollisionTest = true;
			TargetFOV = TPP_FOV;
			break;
		case EBlackoutPerspective::ThirdPersonLeft:
			SpringArmRef->TargetArmLength = 250.0f;
			SpringArmRef->SocketOffset = FVector(0.0f, -45.0f, 50.0f);
			SpringArmRef->bDoCollisionTest = true;
			TargetFOV = TPP_FOV;
			break;
		}
	}
}

void UBlackoutCameraComponent::TogglePerspective()
{
	if (CurrentPerspective == EBlackoutPerspective::FirstPerson)
	{
		SetPerspective(EBlackoutPerspective::ThirdPersonRight);
	}
	else
	{
		SetPerspective(EBlackoutPerspective::FirstPerson);
	}
}

void UBlackoutCameraComponent::ToggleShoulder()
{
	if (CurrentPerspective == EBlackoutPerspective::ThirdPersonRight)
	{
		SetPerspective(EBlackoutPerspective::ThirdPersonLeft);
	}
	else if (CurrentPerspective == EBlackoutPerspective::ThirdPersonLeft)
	{
		SetPerspective(EBlackoutPerspective::ThirdPersonRight);
	}
}

void UBlackoutCameraComponent::DoLandingCameraShake(float FallVelocity)
{
	if (FallVelocity > 400.0f)
	{
		const float PitchOffset = FMath::Clamp((FallVelocity - 400.0f) * 0.01f, 0.0f, 5.0f);
		FRotator CurrentRot = GetRelativeRotation();
		SetRelativeRotation(CurrentRot + FRotator(-PitchOffset, 0.0f, 0.0f));
	}
}

void UBlackoutCameraComponent::UpdateHeadBob(float VelocitySpeed, float DeltaTime)
{
	if (VelocitySpeed > 10.0f)
	{
		HeadBobTimer += DeltaTime * (VelocitySpeed * 0.03f);
		const float BobY = FMath::Sin(HeadBobTimer) * 1.5f;
		const float BobZ = FMath::Cos(HeadBobTimer * 2.0f) * 1.0f;
		SetRelativeLocation(FVector(0.0f, BobY, 60.0f + BobZ));
	}
	else
	{
		HeadBobTimer = 0.0f;
		SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	}
}
