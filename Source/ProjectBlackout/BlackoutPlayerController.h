#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlackoutPlayerController.generated.h"

UCLASS()
class PROJECTBLACKOUT_API ABlackoutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABlackoutPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Touch & Mobile Input Hooks */
	void OnTouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Input")
	bool bEnableTouchControls;
};
