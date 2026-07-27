#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlackoutCharacterState.h"
#include "BlackoutCameraComponent.h"
#include "BlackoutWeaponManager.h"
#include "BlackoutMeleeComponent.h"
#include "BlackoutHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "BlackoutCharacter.generated.h"

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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/** Integrated Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Camera")
	UBlackoutCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Combat")
	UBlackoutWeaponManagerComponent* WeaponManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Combat")
	UBlackoutMeleeComponent* MeleeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Health")
	UBlackoutHealthComponent* HealthComponent;

	/** Current Movement & Locomotion State */
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Movement State")
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

	/** Combat Actions */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Combat Actions")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Combat Actions")
	void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Combat Actions")
	void StartReload();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Combat Actions")
	void PerformMelee();

	UFUNCTION(BlueprintCallable, Category = "Blackout | Camera Actions")
	void TogglePerspective();

	virtual void Jump() override;

private:
	float SlideDurationTimer;
	FVector SlideDirection;

	void UpdateSlide(float DeltaTime);
	bool TraceObstacle(float TraceDistance, float EyeHeightOffset, FHitResult& OutHit) const;
};
