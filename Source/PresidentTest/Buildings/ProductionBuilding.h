// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingActor.h"
#include "PresidentTest/Resources/ResourceActor.h"
#include "ProductionBuilding.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ProductionLog, Log, All);

/**
 * 
 */
UCLASS()
class PRESIDENTTEST_API AProductionBuilding : public ABuildingActor
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool CheckRecipe();
	UFUNCTION(BlueprintCallable)
	void StartProduction();	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class URecipePrimaryAsset> RecipeDataAsset;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTimerHandle ProductionTimerHandle;

protected:

	UFUNCTION()
	void ProduceResource();

private:
	
	UFUNCTION()
	void OnResourceChanged(const UResourcePrimaryAsset* Type);

	UFUNCTION()
	void InitializeMagazine();
};
