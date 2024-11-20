// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"

// Sets default values
ABuildingActor::ABuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	SetRootComponent(SceneRoot);
	BuildingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh Component"));
	BuildingMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

