// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresidentTest/Components/StorageComponent.h"
#include "GameFramework/Actor.h"
#include "VirutalMagazine.generated.h"

class URecipePrimaryAsset;
class UResourcePrimaryAsset;
class AResourceActor;

/**
 * 
 */
UCLASS()
class PRESIDENTTEST_API AVirtualMagazine : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVirtualMagazine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnResourceChanged OnResourceChanged;

	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject"))
	static AVirtualMagazine* GetMagazine(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetResourceAmount(UResourcePrimaryAsset* ResourceType);
	UFUNCTION(BlueprintCallable)
	void SetResourceAmount(UResourcePrimaryAsset* ResourceType, int InAmount);
	UFUNCTION(BlueprintCallable)
	void AddResource(UResourcePrimaryAsset* ResourceType, int ChangeValue);
	UFUNCTION(BlueprintCallable)
	void SubtractResource(UResourcePrimaryAsset* ResourceType, int ChangeValue);
	UFUNCTION(BlueprintCallable)
	bool HasEnoughResource(UResourcePrimaryAsset* ResourceType, int CompareValue);

	UFUNCTION(BlueprintCallable)
	void UseRecipe(URecipePrimaryAsset* Recipe);
	UFUNCTION(BlueprintCallable)
	void TransferResources(UStorageComponent* Storage);

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStorageComponent> StorageComponent;
};
