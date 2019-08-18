// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	  
	//Проверка куда смотрит персонаж 

	FVector PlayerViwePointLocation;//входные журналы
	FRotator PlayerViwePointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViwePointLocation,
		OUT PlayerViwePointRotation);	

	UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), 
		*PlayerViwePointLocation.ToString(), 
		*PlayerViwePointRotation.ToString());
}

