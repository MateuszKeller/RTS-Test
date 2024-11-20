// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionInterface.h"

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.
bool IInteractionInterface::Interact_Implementation(AActor* Requester)
{
	return false;
}

bool IInteractionInterface::PointerHover_Implementation(AActor* Requester)
{
	return false;
}

bool IInteractionInterface::PointerUnHover_Implementation(AActor* Requester)
{
	return false;
}

bool IInteractionInterface::GetInteractionDelay_Implementation(float& InteractionDelay)
{
	return false;
}
