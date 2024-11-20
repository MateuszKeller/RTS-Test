// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PresidentTestGameState.generated.h"

class ABuildingActor;
class AVirtualMagazine;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagazineCreated);

/**
 * 
 */
UCLASS()
class PRESIDENTTEST_API APresidentTestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnMagazineCreated OnMagazineCreated;

protected:
	
	virtual void BeginPlay() override;

public:
	
	UFUNCTION(BlueprintCallable)
	static ABuildingActor* GetNearestWarehouse(AActor* Requester);
	

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AVirtualMagazine> Magazine;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<ABuildingActor*> RegisteredWarehouses;
	
};
