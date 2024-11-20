// Fill out your copyright notice in the Description page of Project Settings.


#include "PresidentTestGameState.h"

#include "PresidentTest/Buildings/BuildingActor.h"
#include "VirutalMagazine.h"
#include "Kismet/GameplayStatics.h"

void APresidentTestGameState::BeginPlay()
{
	Super::BeginPlay();

	Magazine = NewObject<AVirtualMagazine>();
	OnMagazineCreated.Broadcast();
		
}

ABuildingActor* APresidentTestGameState::GetNearestWarehouse(AActor* Requester)
{
	const APresidentTestGameState* GS = Cast<APresidentTestGameState>(UGameplayStatics::GetGameState(Requester));
	if(!GS)
	{
		return nullptr;
	}
	if(GS->RegisteredWarehouses.IsEmpty())
	{
		return nullptr;
	}
	
	float NearestDistance = GS->RegisteredWarehouses[0]->GetDistanceTo(Requester);
	ABuildingActor* Output = GS->RegisteredWarehouses[0];
	for (ABuildingActor* Warehouse : GS->RegisteredWarehouses)
	{
		const float Distance = Warehouse->GetDistanceTo(Requester);
		if(NearestDistance > Distance)
		{
			NearestDistance = Distance;
			Output = Warehouse;
		}
	}

	return Output;
}
