// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCap.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UOpenCap::UOpenCap()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCap::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenCap::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenCap();
	}
}

void UOpenCap::OpenCap()
{
	auto OwnerCap = GetOwner();

	auto NewLocalCap = OwnerCap->GetTransform().GetLocation()+ FVector(0.5f, 0.0f, 0.0f);

	OwnerCap->SetActorLocation(NewLocalCap);

}

