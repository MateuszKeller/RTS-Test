// Copyright Epic Games, Inc. All Rights Reserved.

#include "PresidentTestPlayerController.h"

#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "PresidentTest/Interfaces/InteractionInterface.h"
#include "PresidentTest/AI/SettlerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/LocalPlayer.h"
#include "PresidentTest/Interfaces/ResourceInterface.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APresidentTestPlayerController::APresidentTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void APresidentTestPlayerController::UpdateSelectedSettler(AAIController* InController, ACharacter* InSettler)
{
	SelectedController = InController;
	ControlledActor = InSettler;
}

void APresidentTestPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void APresidentTestPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APresidentTestPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &APresidentTestPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APresidentTestPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &APresidentTestPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &APresidentTestPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &APresidentTestPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &APresidentTestPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &APresidentTestPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APresidentTestPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void APresidentTestPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}
	
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
		if(Hit.GetActor()->Implements<UInteractionInterface>())
		{
			DestinationActor = Hit.GetActor();
		}
		else
		{
			DestinationActor = nullptr;
		}
	}
	
	// Move towards mouse pointer or touch
	// APawn* ControlledPawn = GetPawn();
	// if (ControlledActor != nullptr)
	// {
	// 	FVector WorldDirection = (CachedDestination - ControlledActor->GetActorLocation()).GetSafeNormal();
	// 	ControlledActor->AddMovementInput(WorldDirection, 1.0, false);
	// }
}

void APresidentTestPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		ASettlerAIController* SettlerAIController = Cast<ASettlerAIController>(SelectedController);
		if(DestinationActor)
		{
			if(DestinationActor->Implements<UResourceInterface>())
			{
				SettlerAIController->SetResourceActor(DestinationActor);
			}
			else
			{
				SettlerAIController->ClearResourceActor();
			}

			SettlerAIController->SetNewTarget(DestinationActor);
		}
		else
		{
			SettlerAIController->GetBlackboardComponent()->SetValueAsVector(SettlerAIController->LocationKeyName, CachedDestination);
			SettlerAIController->GetBlackboardComponent()->SetValueAsObject(SettlerAIController->TargetKeyName, nullptr);
		}
		
		// UAIBlueprintHelperLibrary::SimpleMoveToLocation(ControlledActor->GetController(), CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void APresidentTestPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void APresidentTestPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
