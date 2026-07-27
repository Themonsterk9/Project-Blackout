#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BlackoutCameraComponent.generated.h"

UENUM(BlueprintType)
enum class EBlackoutPerspective : uint8
{
	FirstPerson        UMETA(DisplayName = "First Person"),
	ThirdPersonRight   UMETA(DisplayName = "Third Person Right Shoulder"),
	ThirdPersonLeft    UMETA(DisplayName = "Third Person Left Shoulder")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	UBlackoutCameraComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Perspective Management */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera Perspective")
	EBlackoutPerspective CurrentPerspective;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Perspective")
	void SetPerspective(EBlackoutPerspective NewPerspective);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Perspective")
	void TogglePerspective();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Perspective")
	void ToggleShoulder();

	/** FOV Parameters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera FOV")
	float FPP_FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera FOV")
	float TPP_FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera FOV")
	float ADS_FOV;

	/** Spring Arm Reference */
	UPROPERTY(BlueprintReadWrite, Category = "Blackout | Camera Components")
	USpringArmComponent* SpringArmRef;

	/** Camera Sensitivity & Controls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera Settings")
	float MouseSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera Settings")
	float ControllerSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera Settings")
	float TouchSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Camera Settings")
	bool bInvertY;

	/** Camera Effects & Shake Hooks */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Effects")
	void DoLandingCameraShake(float FallVelocity);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Effects")
	void UpdateHeadBob(float VelocitySpeed, float DeltaTime);

private:
	float TargetFOV;
	float HeadBobTimer;
};
