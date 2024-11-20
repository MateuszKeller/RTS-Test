// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SettlerAIController.generated.h"

struct FEnvQueryResult;
class UEnvQuery;
class AResourceActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceTypeChanged);

/**
 * 
 */
UCLASS()
class PRESIDENTTEST_API ASettlerAIController : public AAIController
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintAssignable)
	FOnResourceTypeChanged OnResourceTypeChanged;

	UFUNCTION(BlueprintCallable)
	void SetResourceActor(AActor* ResourceActor);
	UFUNCTION(BlueprintCallable)
	void ClearResourceActor();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FinishInteractionTask();
	UFUNCTION(BlueprintCallable)
	void SetNewTarget(AActor* InNewTarget);
	void MoveToRequestFinished(TSharedPtr<FEnvQueryResult> EnvQueryResult);

	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Runtime")
	TObjectPtr<AActor> LastResourceActor;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Runtime")
	TObjectPtr<class UResourcePrimaryAsset> LastResourceType;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Runtime")
	TObjectPtr<AActor> NewTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Config")
	FName TargetKeyName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Config")
	FName LocationKeyName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Config")
	TObjectPtr<UEnvQuery> MoveToEQS; 
};
