// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresidentTest/Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.generated.h"

UCLASS(Abstract)
class PRESIDENTTEST_API ABuildingActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BuildingMeshComponent;

};
