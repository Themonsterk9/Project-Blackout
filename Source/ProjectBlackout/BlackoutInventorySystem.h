#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BlackoutInventorySystem.generated.h"

UENUM(BlueprintType)
enum class EBlackoutItemType : uint8
{
	Weapon      UMETA(DisplayName = "Weapon"),
	Ammo        UMETA(DisplayName = "Ammunition"),
	Attachment  UMETA(DisplayName = "Weapon Attachment"),
	Helmet      UMETA(DisplayName = "Helmet Armor"),
	Vest        UMETA(DisplayName = "Vest Armor"),
	Healing     UMETA(DisplayName = "Healing Item"),
	Throwable   UMETA(DisplayName = "Throwable Grenade")
};

USTRUCT(BlueprintType)
struct FBlackoutItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	EBlackoutItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Item")
	int32 CurrentQuantity;
};

/** Ground Loot Pickable Actor */
UCLASS()
class PROJECTBLACKOUT_API ABlackoutLootItem : public AActor
{
	GENERATED_BODY()

public:
	ABlackoutLootItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Loot")
	FBlackoutItemData ItemData;

	UFUNCTION(BlueprintCallable, Category = "Blackout | Loot")
	bool PickupLoot(AActor* InstigatorActor);
};

/** Inventory Manager Component */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTBLACKOUT_API UBlackoutInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackoutInventoryComponent();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Inventory Specs")
	int32 MaxSlotCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackout | Inventory Specs")
	float MaxWeightCapacity;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Inventory State")
	TArray<FBlackoutItemData> InventoryItems;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Armor State")
	float HelmetDurability;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Blackout | Armor State")
	float VestDurability;

	/** Inventory Actions */
	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory Actions")
	bool AddItem(FBlackoutItemData NewItem);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory Actions")
	bool RemoveItem(FString ItemID, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory Actions")
	bool UseHealingItem(FString ItemID);

	UFUNCTION(BlueprintCallable, Category = "Blackout | Inventory Actions")
	float GetTotalInventoryWeight() const;
};
