// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresidentTest/Interfaces/InteractionInterface.h"
#include "PresidentTest/Interfaces/ResourceInterface.h"
#include "GameFramework/Actor.h"
#include "ResourceActor.generated.h"

class AResourceActor;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourceDepletedDelegate, AResourceActor*, ResourceActor);


UCLASS()
class PRESIDENTTEST_API UResourcePrimaryAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> Meshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinResourceAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxResourceAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ResourceIcon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ResourceDisplayName = FText::FromString("Resource Name");

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetRandomMesh();
	UFUNCTION(BlueprintCallable)
	int GetRandomAmount();
	
};

UCLASS()
class PRESIDENTTEST_API AResourceActor : public AActor, public IInteractionInterface, public IResourceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceActor();

	UPROPERTY(BlueprintAssignable)
	FResourceDepletedDelegate OnResourceDepleted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;


	// Begin LocationForAI interface
	
	virtual bool Interact_Implementation(AActor* Requester) override;
	virtual bool GetInteractionDelay_Implementation(float& InteractionDelay) override;

	// End LocationForAI interface

	// Begin LocationForAI interface
	
	virtual UResourcePrimaryAsset* GetResourceType_Implementation() override;

	// End LocationForAI interface
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ResourceMeshComponent;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta=(ExposeOnSpawn=true))
	UResourcePrimaryAsset* ResourceDataAsset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Runtime")
	int CurrentResources = 10;

};
