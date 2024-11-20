// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionBuilding.h"

#include "PresidentTest/Core/PresidentTestGameState.h"
#include "PresidentTest/Resources/RecipePrimaryAsset.h"
#include "PresidentTest/Core/VirutalMagazine.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(ProductionLog);

void AProductionBuilding::BeginPlay()
{
	Super::BeginPlay();

	Cast<APresidentTestGameState>(UGameplayStatics::GetGameState(GetWorld()))->OnMagazineCreated.AddDynamic(this, &AProductionBuilding::InitializeMagazine);
	if(AVirtualMagazine::GetMagazine(GetWorld()))
	{
		InitializeMagazine();
	}
}

bool AProductionBuilding::CheckRecipe()
{
	AVirtualMagazine* Magazine = AVirtualMagazine::GetMagazine(GetWorld());
	for (const TTuple<UResourcePrimaryAsset*, int>& Ingredient : RecipeDataAsset->Ingredients)
	{
		if(!Magazine->HasEnoughResource(Ingredient.Key, Ingredient.Value))
		{
			return false;
		}
	}
	
	return true;
}

void AProductionBuilding::StartProduction()
{
	if(ProductionTimerHandle.IsValid())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(ProductionTimerHandle, this, &AProductionBuilding::ProduceResource, RecipeDataAsset->ProductionTime, false);
	
	AVirtualMagazine* Magazine = AVirtualMagazine::GetMagazine(GetWorld());
	Magazine->UseRecipe(RecipeDataAsset);
}

void AProductionBuilding::ProduceResource()
{	
	AVirtualMagazine* Magazine = AVirtualMagazine::GetMagazine(GetWorld());
	Magazine->AddResource(RecipeDataAsset->ProductType, RecipeDataAsset->ProduceAmount);
	UE_LOG(ProductionLog, Log, TEXT("Resource Procuced %s: %d"), *RecipeDataAsset->ProductType->ResourceDisplayName.ToString(), Magazine->GetResourceAmount(RecipeDataAsset->ProductType))

	GetWorld()->GetTimerManager().ClearTimer(ProductionTimerHandle);
	if(CheckRecipe())
	{
		StartProduction();
	}
}

void AProductionBuilding::OnResourceChanged(const UResourcePrimaryAsset* Type)
{
	if(ProductionTimerHandle.IsValid() || !RecipeDataAsset->Ingredients.Contains(Type))
	{
		return;
	}

	if(CheckRecipe())
	{
		StartProduction();
	}
	
}

void AProductionBuilding::InitializeMagazine()
{
	AVirtualMagazine::GetMagazine(GetWorld())->OnResourceChanged.AddDynamic(this, &AProductionBuilding::OnResourceChanged);
	Cast<APresidentTestGameState>(UGameplayStatics::GetGameState(GetWorld()))->OnMagazineCreated.RemoveDynamic(this, &AProductionBuilding::InitializeMagazine);
}