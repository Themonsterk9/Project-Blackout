#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlackoutCharacterState.h"
#include "BlackoutAnimInstance.generated.h"

class ABlackoutCharacter;

UCLASS()
class PROJECTBLACKOUT_API UBlackoutAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBlackoutAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	ABlackoutCharacter* CharacterOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsProne;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	bool bIsVaulting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackout | Animation")
	EBlackoutCharacterState CharacterState;
};
