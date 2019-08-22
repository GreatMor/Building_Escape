// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Engine/Public/DrawDebugHelpers.h"

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

	PhysicsHandel = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandel)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s no component "), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Inputcomponent "), *GetOwner()->GetName());
		///����������� �������� 
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s no Inputcomponent "), *GetOwner()->GetName());
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	  
	//�������� ���� ������� �������� 

	FVector PlayerViwePointLocation;//������� �������
	FRotator PlayerViwePointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViwePointLocation,
		OUT PlayerViwePointRotation);	

	FVector LintraceEnd = PlayerViwePointLocation + PlayerViwePointRotation.Vector() * Reach;

	/*UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), 
		*PlayerViwePointLocation.ToString(), 
		*PlayerViwePointRotation.ToString());*/

	DrawDebugLine
	(
		GetWorld(),
		PlayerViwePointLocation,
		LintraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		5.f
	);
	
	FCollisionQueryParams TraceParametrs(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViwePointLocation,
		LintraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParametrs
	);

	AActor* ActorHit = Hit.GetActor(); // ��������� �� ����� ������ �������� ������������ 
		if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor hit : %s "), *(ActorHit->GetName()));
	}

		
		 
	
}

