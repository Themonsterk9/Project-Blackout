#include "BlackoutUISystem.h"

void UBlackoutWidgetBase::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBlackoutWidgetBase::HideWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBlackoutHUDWidget::UpdateHUDValues(float Health, float Armor, int32 AmmoInMag, int32 ReserveAmmo, FString WeaponName)
{
}

void UBlackoutHUDWidget::AddKillFeedEntry(FString KillerName, FString VictimName, FString WeaponUsed)
{
}

void UBlackoutMinimapWidget::UpdateMinimapIcons(FVector PlayerLocation, float PlayerYaw, const TArray<FVector>& Teammates, FVector SafeZoneCenter, float SafeZoneRadius)
{
}

void UBlackoutInventoryWidget::RefreshInventoryGrid()
{
}

void UBlackoutMainMenuWidget::OpenTab(FString TabName)
{
}

void UBlackoutMatchSummaryWidget::PopulateMatchSummary(bool bVictory, int32 Kills, int32 Score, int32 XPEarned, int32 RankPointsDelta)
{
}

void UBlackoutMobileLayoutWidget::SetTouchControlScale(float ScaleFactor)
{
}
