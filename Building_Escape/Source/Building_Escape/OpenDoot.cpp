// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoot.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"

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
	
	//Find the owning Actor 
	auto Owner = GetOwner();

	// Create a rotation 
	auto NewRotation = FRotator(0.0f, 60.0f, 0.0f);

	//Set the door rotation
	Owner->SetActorRotation(NewRotation);
	
}


// Called every frame
void UOpenDoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

