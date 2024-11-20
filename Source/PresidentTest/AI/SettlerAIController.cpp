// Fill out your copyright notice in the Description page of Project Settings.


#include "SettlerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "PresidentTest/Interfaces/ResourceInterface.h"

void ASettlerAIController::SetResourceActor(AActor* ResourceActor)
{
	LastResourceActor = ResourceActor;
	LastResourceType = IResourceInterface::Execute_GetResourceType(ResourceActor);

	OnResourceTypeChanged.Broadcast();
}

void ASettlerAIController::ClearResourceActor()
{
	LastResourceActor = nullptr;
	LastResourceType = nullptr;

	OnResourceTypeChanged.Broadcast();
}

void ASettlerAIController::SetNewTarget(AActor* InNewTarget)
{
	if(!InNewTarget)
	{
		return;
	}

	NewTarget = InNewTarget;

	FEnvQueryRequest Request = FEnvQueryRequest(MoveToEQS, NewTarget);
	Request.Execute(EEnvQueryRunMode::SingleResult, this, &ASettlerAIController::MoveToRequestFinished);

}

void ASettlerAIController::MoveToRequestFinished(TSharedPtr<FEnvQueryResult> EnvQueryResult)
{
	FVector NewLocationToMove = NewTarget->GetActorLocation();
	if(EnvQueryResult->IsSuccessful())
	{
		NewLocationToMove = EnvQueryResult->GetItemAsLocation(0);
	}

	UObject* LastTarget = Blackboard->GetValueAsObject(TargetKeyName);
	Blackboard->SetValueAsObject(TargetKeyName, NewTarget);

	if(LastTarget != NewTarget)
	{
		Blackboard->SetValueAsVector(LocationKeyName, NewLocationToMove);
	}

	FinishInteractionTask();
}
