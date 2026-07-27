#include "BlackoutSecurityManager.h"
#include "Misc/SecureHash.h"
#include "Misc/Base64.h"

UBlackoutAntiCheatSubsystem::UBlackoutAntiCheatSubsystem()
{
}

void UBlackoutSecurityManager_Init()
{
}

void UBlackoutAntiCheatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UBlackoutAntiCheatSubsystem::ValidateMovement(ACharacter* Character, FVector NewLocation, float DeltaTime)
{
	if (!Character || DeltaTime <= 0.0f) return true;

	const FVector OldLocation = Character->GetActorLocation();
	const float DistanceMoved = FVector::Dist(OldLocation, NewLocation);
	const float Speed = DistanceMoved / DeltaTime;

	// Teleport Detection (> 1500 units in single frame)
	if (DistanceMoved > 1500.0f)
	{
		LogSecurityViolation(Character->GetName(), TEXT("Teleportation_Detected"), FString::Printf(TEXT("Moved %.1f units in frame"), DistanceMoved));
		return false;
	}

	// Speed Hack Detection (> 1000 cm/s sustained speed)
	if (Speed > 1000.0f)
	{
		LogSecurityViolation(Character->GetName(), TEXT("SpeedHack_Detected"), FString::Printf(TEXT("Speed %.1f cm/s exceeds cap"), Speed));
		return false;
	}

	return true;
}

bool UBlackoutAntiCheatSubsystem::ValidateFireRate(FString WeaponID, float TimeBetweenShots)
{
	if (TimeBetweenShots < 0.05f) // Cap at 1200 RPM
	{
		LogSecurityViolation(TEXT("Client"), TEXT("RapidFire_Detected"), FString::Printf(TEXT("Interval %.3f too low for %s"), TimeBetweenShots, *WeaponID));
		return false;
	}
	return true;
}

bool UBlackoutAntiCheatSubsystem::ValidateDamageAmount(float CalculatedDamage, float MaxAllowedDamage)
{
	if (CalculatedDamage > MaxAllowedDamage * 1.05f)
	{
		LogSecurityViolation(TEXT("Client"), TEXT("DamageHack_Detected"), FString::Printf(TEXT("Damage %.1f exceeds max %.1f"), CalculatedDamage, MaxAllowedDamage));
		return false;
	}
	return true;
}

FString UBlackoutAntiCheatSubsystem::EncryptSavePayload(FString PlainText) const
{
	return FBase64::Encode(PlainText);
}

FString UBlackoutAntiCheatSubsystem::DecryptSavePayload(FString CipherText) const
{
	FString Decoded;
	FBase64::Decode(CipherText, Decoded);
	return Decoded;
}

FString UBlackoutAntiCheatSubsystem::SanitizeInputString(FString RawInput) const
{
	FString Clean = RawInput.Replace(TEXT("<"), TEXT("")).Replace(TEXT(">"), TEXT("")).Replace(TEXT("'"), TEXT(""));
	return Clean.Left(64);
}

void UBlackoutAntiCheatSubsystem::LogSecurityViolation(FString PlayerID, FString ViolationType, FString Details)
{
	FBlackoutSecurityLog Log;
	Log.PlayerID = PlayerID;
	Log.ViolationType = ViolationType;
	Log.Details = Details;
	Log.Timestamp = FDateTime::Now().ToString();
	AuditLogs.Add(Log);
}
