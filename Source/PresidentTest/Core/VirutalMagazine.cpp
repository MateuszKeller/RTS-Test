// Fill out your copyright notice in the Description page of Project Settings.


#include "VirutalMagazine.h"

#include "PresidentTestGameState.h"
#include "PresidentTest/Resources/RecipePrimaryAsset.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVirtualMagazine::AVirtualMagazine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("Storage Component"));
}

// Called when the game starts or when spawned
void AVirtualMagazine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVirtualMagazine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AVirtualMagazine* AVirtualMagazine::GetMagazine(const UObject* WorldContextObject)
{
	if(APresidentTestGameState* GS = Cast<APresidentTestGameState>(UGameplayStatics::GetGameState(WorldContextObject)))
	{
		return GS->Magazine;
	}
	
	return nullptr;
}

int AVirtualMagazine::GetResourceAmount(UResourcePrimaryAsset* ResourceType)
{
	return StorageComponent->GetResourceAmount(ResourceType);
}

void AVirtualMagazine::SetResourceAmount(UResourcePrimaryAsset* ResourceType, int InAmount)
{
	StorageComponent->SetResourceAmount(ResourceType, InAmount);
}

void AVirtualMagazine::AddResource(UResourcePrimaryAsset* ResourceType, int ChangeValue)
{
	StorageComponent->AddResource(ResourceType, ChangeValue);
	OnResourceChanged.Broadcast(ResourceType);
}

void AVirtualMagazine::SubtractResource(UResourcePrimaryAsset* ResourceType, int ChangeValue)
{
	StorageComponent->SubtractResource(ResourceType, ChangeValue);
	OnResourceChanged.Broadcast(ResourceType);
}

void AVirtualMagazine::UseRecipe(URecipePrimaryAsset* Recipe)
{
	for (const TTuple<UResourcePrimaryAsset*, int>& Ingredient : Recipe->Ingredients)
	{
		SubtractResource(Ingredient.Key, Ingredient.Value);
	}
}

void AVirtualMagazine::TransferResources(UStorageComponent* Storage)
{
	for (UResourcePrimaryAsset* ResourceType : Storage->GetAllResourceTypesInStorage())
	{
		const int ToAdd = Storage->GetResourceAmount(ResourceType);
		AddResource(ResourceType, ToAdd);
	}

	Storage->EmptyStorage();
}

bool AVirtualMagazine::HasEnoughResource(UResourcePrimaryAsset* ResourceType, int CompareValue)
{
	return GetResourceAmount(ResourceType) >= CompareValue;
}
