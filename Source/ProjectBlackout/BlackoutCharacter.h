#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlackoutCharacterState.h"
#include "BlackoutCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Config=Game)
class PROJECTBLACKOUT_API ABlackoutCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABlackoutCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

public:
	/** Current Movement & Locomotion State */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Movement State")
	EBlackoutCharacterState CurrentState;

	/** Configurable Movement & Capsule Parameters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Config")
	FBlackoutMovementConfig MovementConfig;

	/** State Machine Transition Checks */
	UFUNCTION(BlueprintCallable, Category = "Blackout | State Machine")
	bool CanTransitionToState(EBlackoutCharacterState NewState) const;

	UFUNCTION(BlueprintCallable, Category = "Blackout | State Machine")
	bool SetCharacterState(EBlackoutCharacterState NewState);

	/** Movement Input Handlers */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Movement")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Movement")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Movement")
	void TurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Movement")
	void LookUpAtRate(float Rate);

	/** Actions */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void StopSprint();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void StartCrouch();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void StopCrouch();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void ToggleProne();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void StartSlide();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void TryVault();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Actions")
	void TryClimb();

	/** Custom Jump Override */
	virtual void Jump() override;

private:
	/** Slide State Internal */
	float SlideDurationTimer;
	FVector SlideDirection;

	/** Internal Helper Routines */
	void UpdateSlide(float DeltaTime);
	bool TraceObstacle(float TraceDistance, float EyeHeightOffset, FHitResult& OutHit) const;
};
