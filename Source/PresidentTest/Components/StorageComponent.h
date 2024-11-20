// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StorageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceChanged, const UResourcePrimaryAsset*, ResourceType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourcesEmptied);

class UResourcePrimaryAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRESIDENTTEST_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStorageComponent();

	UPROPERTY(BlueprintAssignable)
	FOnResourceChanged OnResourceChanged;
	UPROPERTY(BlueprintAssignable)
	FOnResourcesEmptied OnResourcesEmptied;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetResourceAmount(UResourcePrimaryAsset* ResourceClass);
	UFUNCTION(BlueprintCallable)
	void SetResourceAmount(UResourcePrimaryAsset* ResourceClass, int InAmount);
	UFUNCTION(BlueprintCallable)
	void AddResource(UResourcePrimaryAsset* ResourceClass, int ChangeValue);
	UFUNCTION(BlueprintCallable)
	void SubtractResource(UResourcePrimaryAsset* ResourceClass, int ChangeValue);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UResourcePrimaryAsset*> GetAllResourceTypesInStorage();
	UFUNCTION(BlueprintCallable)
	void EmptyStorage();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool WithinLimit();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(InlineEditConditionToggle))
	bool bHasLimit = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bHasLimit"))
	int StorageLimit = INT_MAX;
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	TMap<UResourcePrimaryAsset*, int> Resources;	
};
