#include "BlackoutPlayerController.h"
#include "Engine/World.h"

ABlackoutPlayerController::ABlackoutPlayerController()
{
	bEnableTouchControls = false;
}

void ABlackoutPlayerController::BeginPlay()
{
	Super::BeginPlay();

#if PLATFORM_ANDROID || PLATFORM_IOS
	bEnableTouchControls = true;
	bShowMouseCursor = false;
#endif
}

void ABlackoutPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindTouch(IE_Pressed, this, &ABlackoutPlayerController::OnTouchStarted);
		InputComponent->BindTouch(IE_Released, this, &ABlackoutPlayerController::OnTouchStopped);
	}
}

void ABlackoutPlayerController::OnTouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// Virtual joystick & touch input handler for mobile target platform readiness
}

void ABlackoutPlayerController::OnTouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	// Virtual joystick touch release handler
}
