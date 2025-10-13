// developed by Neko


#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/Items/ItemBase.h"
#include "Character/SurvCharacter.h"
#include "Actors/PickupActor.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	ASurvCharacter* tOwner = Cast<ASurvCharacter>(GetOwner());
	if (tOwner)
	{
		Owner = tOwner;
	}
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::AddItemToTop(const TSubclassOf<UItemBase> Item)
{
	if (!IsValid(Item))
	{
		//TODO: add error logging for invalid item; 
		return false;
	}
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	InventoryContents.Insert(Item,0);
	CurrentWeight += ItemWeight;
	return true;
}

bool UInventoryComponent::AddItemAtIndex(TSubclassOf<UItemBase> Item, int& Index)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	if (Index > InventoryContents.Num())
	{
		Index = InventoryContents.Num();
	}
	InventoryContents.Insert(Item,Index);
	CurrentWeight += ItemWeight;
	return true;
}

bool UInventoryComponent::AddItemToStackAtIndex(TSubclassOf<UItemBase> Item, const int& Index)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	if (Index > InventoryContents.Num())
	{
		//TODO: add error logging
		return false;
	}

	UItemBase* TargetItem = Cast<UItemBase>(InventoryContents[Index]);
	int remain = TargetItem->AddToStack(Item.GetDefaultObject()->GetCurrentStack());
	if (remain > 0)
	{
		Item.GetDefaultObject()->SetStackSize(remain);
		InventoryContents.Insert(Item,0);
	}
	CurrentWeight += ItemWeight;
	return true;
}

TArray<FItemUIData> UInventoryComponent::GetInventoryUIData() const
{
	TArray<FItemUIData> Ret;
	
	for (int idx = 0; idx < InventoryContents.Num(); idx++)
	{
		Ret.Add(InventoryContents[idx].GetDefaultObject()->GetItemUIData(idx));
	}

	return Ret;
}

bool UInventoryComponent::UseItemAtIndex(const int32& Index)
{
	if (Owner == nullptr || Index >= InventoryContents.Num())
	{
		//TODO: Handle error logging
		return false;
	}

	InventoryContents[Index].GetDefaultObject()->OnUse(Owner);
	InventoryContents[Index].GetDefaultObject()->RemoveFromStack(1);
	CurrentWeight -= InventoryContents[Index].GetDefaultObject()->GetItemWeight();
	if(InventoryContents[Index].GetDefaultObject()->GetCurrentStack() == 0)
	{
		InventoryContents.RemoveAt(Index);
	}
	return true;
}

bool UInventoryComponent::DropStackAtIndex(const int32& Index)
{
	if (Owner == nullptr || Index >= InventoryContents.Num())
	{
		//TODO: Handle error logging
		return false;
	}
	
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 50));
	APickupActor* SpawnedItem = GetWorld()->SpawnActor<APickupActor>(APickupActor::StaticClass(), SpawnTrans);
	SpawnedItem->SetActorTransform(SpawnTrans);

	SpawnedItem->SetPickupMesh(InventoryContents[Index].GetDefaultObject()->GetPickupMesh());
	SpawnedItem->SetWasSpawned(true);

	TSubclassOf<UItemBase> PickupItem = InventoryContents[Index];
	SpawnedItem->SetInventoryItem(PickupItem);
	InventoryContents.RemoveAt(Index);
	CurrentWeight -= PickupItem.GetDefaultObject()->GetStackWeight();
	return true;
}

bool UInventoryComponent::IsOverCarryWeight(const float& ItemWeight) const
{
	if(CurrentWeight + ItemWeight > MaxWeight)
	{
		return true;
	}
	return false;
}
