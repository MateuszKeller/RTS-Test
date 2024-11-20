// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RecipePrimaryAsset.generated.h"

class UResourcePrimaryAsset;

/**
 * 
 */
UCLASS()
class PRESIDENTTEST_API URecipePrimaryAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UResourcePrimaryAsset*, int> Ingredients;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UResourcePrimaryAsset* ProductType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=1))
	int ProduceAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductionTime = 1.f;
	
};
