// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceActor.h"

#include "PresidentTest/Core/PresidentTestPlayerController.h"
#include "PresidentTest/Components/StorageComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UStaticMesh* UResourcePrimaryAsset::GetRandomMesh()
{
	if(Meshes.IsEmpty())
	{
		return nullptr;
	}
	
	const int RandomIndex = FMath::RandHelper(Meshes.Num());
	return Meshes[RandomIndex];
}

int UResourcePrimaryAsset::GetRandomAmount()
{
	return FMath::RandRange(MinResourceAmount, MaxResourceAmount);
}


///////////		AResourceActor		///////////
///
// Sets default values
AResourceActor::AResourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	SetRootComponent(SceneRoot);
	ResourceMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Resource Mesh Component"));
	ResourceMeshComponent->SetupAttachment(RootComponent);

	// if(ResourceDataAsset)
	// {
	// 	ResourceMeshComponent->SetStaticMesh(ResourceDataAsset->GetRandomMesh());
	// 	CurrentResources = ResourceDataAsset->GetRandomAmount();
	// }
}

// Called when the game starts or when spawned
void AResourceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(ResourceDataAsset)
	{
		ResourceMeshComponent->SetStaticMesh(ResourceDataAsset->GetRandomMesh());
		CurrentResources = ResourceDataAsset->GetRandomAmount();
	}
}

void AResourceActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	ACharacter* Settler = Cast<APresidentTestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ControlledActor;
	const float Distance = GetDistanceTo(Settler);
	if(Distance < 170.f)
	{
		IInteractionInterface::Execute_Interact(this, Settler);
	}
	
}

void AResourceActor::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Hand;
}

void AResourceActor::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
}

bool AResourceActor::Interact_Implementation(AActor* Requester)
{	
	UStorageComponent* Storage = Requester->FindComponentByClass<UStorageComponent>();
	if(!Storage)
	{
		return false;
	}
	if(!Storage->WithinLimit())
	{
		return false;
	}
	
	Storage->AddResource(ResourceDataAsset, 1);
	CurrentResources--;
	
	// APresidentTestCharacter* Settler = Cast<APresidentTestCharacter>(Requester);
	// if(CurrentResources > 0 && Settler)
	// {
	// 	const TSubclassOf<AResourceActor> C = GetClass();
	// 	if(Settler->TEMPResourceClass == C && Settler->BackpackLimit > Settler->TEMPResources)
	// 	{
	// 		Settler->TEMPResources++;
	// 	}
	// 	else
	// 	{
	// 		return false;
	// 	}
	// 			
	// 	CurrentResources--;
	// }
	
	if(CurrentResources <= 0)
	{
		OnResourceDepleted.Broadcast(this);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
		Destroy();
	}
	
	return true;
}

bool AResourceActor::GetInteractionDelay_Implementation(float& InteractionDelay)
{
	InteractionDelay = 1.f;
	return true;
}

UResourcePrimaryAsset* AResourceActor::GetResourceType_Implementation()
{
	return ResourceDataAsset;
}



