// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	 FindPhysicsHandleComponent();

	 SetupInputComponent();
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Inputcomponent "), *GetOwner()->GetName());
		///����������� �������� 
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s no Inputcomponent "), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindPhysicsComponent = true"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s no component "), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"));	
	//��������� ��� � ��������� ���������� �� ������ � ������������ ���������� ���������� ���� 	
	auto HitResult = GetFirstPhysicsBodyInReach();
	//�������� ��������� �� �������� ���������� �����
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();
	//���� �� ��������� �� ������ ������ �������� �� ���� �� ��������� ���������� �����
	if (ActorHit)
	{		
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), FRotator(0,0,0));
	}
}
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FVector PlayerViwePointLocation;//������� �������
	FRotator PlayerViwePointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViwePointLocation,
		OUT PlayerViwePointRotation);

	FVector LintraceEnd = PlayerViwePointLocation + (PlayerViwePointRotation.Vector() * Reach);

	////���� ���������� ����� �����������

	
	//�� �� ������ ������� ��������� 
	PhysicsHandle->SetTargetLocation(LintraceEnd);
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release"));
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViwePointLocation;//������� �������
	FRotator PlayerViwePointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViwePointLocation,
		OUT PlayerViwePointRotation);

	FVector LintraceEnd = PlayerViwePointLocation + PlayerViwePointRotation.Vector() * Reach;

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

	return Hit;
}
