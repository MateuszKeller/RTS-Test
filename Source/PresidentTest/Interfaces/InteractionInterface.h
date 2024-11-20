// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRESIDENTTEST_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Interact(AActor* Requester);
	virtual bool Interact_Implementation(AActor* Requester);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool PointerHover(AActor* Requester);
	virtual bool PointerHover_Implementation(AActor* Requester);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool PointerUnHover(AActor* Requester);
	virtual bool PointerUnHover_Implementation(AActor* Requester);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetInteractionDelay(float& InteractionDelay );
	virtual bool GetInteractionDelay_Implementation(float& InteractionDelay);
};
