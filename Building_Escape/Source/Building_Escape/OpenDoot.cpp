// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoot.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/World.h"

#define OUT

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

	
	Owner = GetOwner();
}

// Called every frame
void UOpenDoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate()>50.f)
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

float UOpenDoot::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0;

	//перечисление всех акторов которые пересикаются с платформой 
	TArray<AActor*>OwerlappingActors;

	PressurePlate->GetOverlappingActors(OUT OwerlappingActors);
	
	for (const auto& Actor : OwerlappingActors)
	{
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s On pressed paket "), *Actor->GetName());
	}
	return TotalMass;
}


