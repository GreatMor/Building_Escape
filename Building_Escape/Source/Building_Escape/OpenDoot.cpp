// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoot.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoot::UOpenDoot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoot::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

// Called every frame
void UOpenDoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTiame = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds()-LastDoorOpenTiame > OpenDoorDeley)
	{
		CloseDoor();
	}
}

void UOpenDoot::OpenDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngl, 0.0f));
}
void UOpenDoot::CloseDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 90.f, 0.0f));
}


