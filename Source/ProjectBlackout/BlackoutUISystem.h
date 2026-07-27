#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackoutUISystem.generated.h"

/** Base User Widget for Project Blackout */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | UI")
	void ShowWidget();

	UFUNCTION(BlueprintCallable, Category = "Blackout | UI")
	void HideWidget();
};

/** Tactical HUD Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutHUDWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | HUD")
	void UpdateHUDValues(float Health, float Armor, int32 AmmoInMag, int32 ReserveAmmo, FString WeaponName);

	UFUNCTION(BlueprintCallable, Category = "Blackout | HUD")
	void AddKillFeedEntry(FString KillerName, FString VictimName, FString WeaponUsed);
};

/** Minimap Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutMinimapWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | Minimap")
	void UpdateMinimapIcons(FVector PlayerLocation, float PlayerYaw, const TArray<FVector>& Teammates, FVector SafeZoneCenter, float SafeZoneRadius);
};

/** Inventory UI Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutInventoryWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory UI")
	void RefreshInventoryGrid();
};

/** Main Menu Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutMainMenuWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | Main Menu")
	void OpenTab(FString TabName);
};

/** Match Summary Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutMatchSummaryWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | Match Summary")
	void PopulateMatchSummary(bool bVictory, int32 Kills, int32 Score, int32 XPEarned, int32 RankPointsDelta);
};

/** Mobile Touch Overlay Widget */
UCLASS()
class PROJECTBLACKOUT_API UBlackoutMobileLayoutWidget : public UBlackoutWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blackout | Mobile UI")
	void SetTouchControlScale(float ScaleFactor);
};
