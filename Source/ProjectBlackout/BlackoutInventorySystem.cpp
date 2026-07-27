#include "BlackoutInventorySystem.h"
#include "BlackoutHealthComponent.h"
#include "GameFramework/Actor.h"

ABlackoutLootItem::ABlackoutLootItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ItemData.ItemID = TEXT("Loot_FirstAid");
	ItemData.ItemName = TEXT("First Aid Kit");
	ItemData.ItemType = EBlackoutItemType::Healing;
	ItemData.Weight = 0.5f;
	ItemData.MaxStackSize = 5;
	ItemData.CurrentQuantity = 1;
}

bool ABlackoutLootItem::PickupLoot(AActor* InstigatorActor)
{
	if (InstigatorActor)
	{
		UBlackoutInventoryComponent* InvComp = InstigatorActor->FindComponentByClass<UBlackoutInventoryComponent>();
		if (InvComp && InvComp->AddItem(ItemData))
		{
			Destroy();
			return true;
		}
	}
	return false;
}

UBlackoutInventoryComponent::UBlackoutInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	MaxSlotCapacity = 20;
	MaxWeightCapacity = 30.0f;
	HelmetDurability = 100.0f;
	VestDurability = 100.0f;
}

void UBlackoutInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBlackoutInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBlackoutInventoryComponent, InventoryItems);
	DOREPLIFETIME(UBlackoutInventoryComponent, HelmetDurability);
	DOREPLIFETIME(UBlackoutInventoryComponent, VestDurability);
}

bool UBlackoutInventoryComponent::AddItem(FBlackoutItemData NewItem)
{
	if (GetTotalInventoryWeight() + (NewItem.Weight * NewItem.CurrentQuantity) > MaxWeightCapacity)
	{
		return false;
	}

	for (FBlackoutItemData& Item : InventoryItems)
	{
		if (Item.ItemID == NewItem.ItemID && Item.CurrentQuantity < Item.MaxStackSize)
		{
			const int32 SpaceLeft = Item.MaxStackSize - Item.CurrentQuantity;
			const int32 AddAmount = FMath::Min(SpaceLeft, NewItem.CurrentQuantity);
			Item.CurrentQuantity += AddAmount;
			NewItem.CurrentQuantity -= AddAmount;
			if (NewItem.CurrentQuantity <= 0)
			{
				return true;
			}
		}
	}

	if (InventoryItems.Num() < MaxSlotCapacity && NewItem.CurrentQuantity > 0)
	{
		InventoryItems.Add(NewItem);
		return true;
	}

	return false;
}

bool UBlackoutInventoryComponent::RemoveItem(FString ItemID, int32 Quantity)
{
	for (int32 i = 0; i < InventoryItems.Num(); ++i)
	{
		if (InventoryItems[i].ItemID == ItemID)
		{
			if (InventoryItems[i].CurrentQuantity <= Quantity)
			{
				InventoryItems.RemoveAt(i);
			}
			else
			{
				InventoryItems[i].CurrentQuantity -= Quantity;
			}
			return true;
		}
	}
	return false;
}

bool UBlackoutInventoryComponent::UseHealingItem(FString ItemID)
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		UBlackoutHealthComponent* HealthComp = Owner->FindComponentByClass<UBlackoutHealthComponent>();
		if (HealthComp && !HealthComp->IsDead())
		{
			HealthComp->Heal(50.0f);
			RemoveItem(ItemID, 1);
			return true;
		}
	}
	return false;
}

float UBlackoutInventoryComponent::GetTotalInventoryWeight() const
{
	float Total = 0.0f;
	for (const FBlackoutItemData& Item : InventoryItems)
	{
		Total += Item.Weight * Item.CurrentQuantity;
	}
	return Total;
}
