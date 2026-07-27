#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/Character.h"
#include "BlackoutSecurityManager.generated.h"

USTRUCT(BlueprintType)
struct FBlackoutSecurityLog
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Security Log")
	FString PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Security Log")
	FString ViolationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Security Log")
	FString Details;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Security Log")
	FString Timestamp;
};

UCLASS()
class PROJECTBLACKOUT_API UBlackoutAntiCheatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBlackoutAntiCheatSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Movement & Server Authority Validation */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Anti-Cheat")
	bool ValidateMovement(ACharacter* Character, FVector NewLocation, float DeltaTime);

	/** Combat Validation */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Anti-Cheat")
	bool ValidateFireRate(FString WeaponID, float TimeBetweenShots);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Anti-Cheat")
	bool ValidateDamageAmount(float CalculatedDamage, float MaxAllowedDamage);

	/** Data Encryption & Protection */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Security")
	FString EncryptSavePayload(FString PlainText) const;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Security")
	FString DecryptSavePayload(FString CipherText) const;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Security")
	FString SanitizeInputString(FString RawInput) const;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Security Log")
	void LogSecurityViolation(FString PlayerID, FString ViolationType, FString Details);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Security Log")
	TArray<FBlackoutSecurityLog> AuditLogs;
};
