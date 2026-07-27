#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackoutProgressionSystem.h"
#include "BlackoutCustomizationSystem.generated.h"

USTRUCT(BlueprintType)
struct FBlackoutLoadout
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString LoadoutName = TEXT("Custom Loadout");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString PrimaryWeaponID = TEXT("Wep_M4A1");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString SecondaryWeaponID = TEXT("Wep_MP5");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString SidearmID = TEXT("Wep_P18");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString MeleeID = TEXT("Melee_Knife");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadout")
	FString GrenadeType = TEXT("Item_Frag");
};

USTRUCT(BlueprintType)
struct FBlackoutPlayerProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	FString Username = TEXT("Operator");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	FString AvatarID = TEXT("Avatar_Default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	FString BannerID = TEXT("Banner_Default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	EBlackoutCompetitiveRank Rank = EBlackoutCompetitiveRank::Bronze;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	int32 PlayerLevel = 1;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackoutCustomizationComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Character Appearance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Appearance")
	int32 FacePresetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Appearance")
	int32 SkinToneID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Appearance")
	int32 HairStyleID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Appearance")
	FString OutfitID;

	/** Weapon Skins Map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Weapon Skins")
	TMap<FString, FString> WeaponSkins;

	/** Emote Wheel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Emotes")
	TArray<FString> EquippedEmotes;

	/** Loadouts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadouts")
	TArray<FBlackoutLoadout> SavedLoadouts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loadouts")
	int32 ActiveLoadoutIndex;

	/** Profile Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Profile")
	FBlackoutPlayerProfile PlayerProfile;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Customization")
	void EquipWeaponSkin(FString WeaponID, FString SkinID);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Customization")
	void SelectLoadout(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Customization")
	void SaveLoadout(int32 SlotIndex, const FBlackoutLoadout& NewLoadout);
};
