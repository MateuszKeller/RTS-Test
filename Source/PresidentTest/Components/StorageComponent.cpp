// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageComponent.h"

// Sets default values for this component's properties
UStorageComponent::UStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UStorageComponent::GetResourceAmount(UResourcePrimaryAsset* ResourceClass)
{
	const int* Amount = Resources.Find(ResourceClass);
	return Amount ? *Amount : 0;
}

void UStorageComponent::SetResourceAmount(UResourcePrimaryAsset* ResourceClass, int InAmount)
{
	Resources.Add(ResourceClass, InAmount);
	OnResourceChanged.Broadcast(ResourceClass);
}

void UStorageComponent::AddResource(UResourcePrimaryAsset* ResourceClass, int ChangeValue)
{
	if(int* Amount = Resources.Find(ResourceClass))
	{
		*Amount += ChangeValue;
	}
	else
	{
		Resources.Add(ResourceClass, ChangeValue);
	}
	OnResourceChanged.Broadcast(ResourceClass);
}

void UStorageComponent::SubtractResource(UResourcePrimaryAsset* ResourceClass, int ChangeValue)
{
	if(int* Amount = Resources.Find(ResourceClass))
	{
		*Amount -= ChangeValue;
	}
	OnResourceChanged.Broadcast(ResourceClass);
}

TArray<UResourcePrimaryAsset*> UStorageComponent::GetAllResourceTypesInStorage()
{
	TArray<UResourcePrimaryAsset*> Output;
	Resources.GetKeys(Output);
	return Output;
}

void UStorageComponent::EmptyStorage()
{
	Resources.Empty();
	OnResourcesEmptied.Broadcast();
}

bool UStorageComponent::WithinLimit()
{
	if(!bHasLimit)
	{
		return true;
	}

	int Sum = 0;
	for (UResourcePrimaryAsset* ResourceType : GetAllResourceTypesInStorage())
	{
		Sum += GetResourceAmount(ResourceType);
	}

	return StorageLimit > Sum;
}
