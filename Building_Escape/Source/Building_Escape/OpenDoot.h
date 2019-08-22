// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

//вернёт обшую массу акторов на пластине 
	float GetTotalMassOfActorsOnPlate();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	
	UPROPERTY(VisibleAnywhere)
	float OpenAngl = 60.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate;

	//UPROPERTY(EditAnywhere)


	AActor * Owner;// этор обладающий дверью

	UPROPERTY(EditAnywhere)
	float OpenDoorDeley = 5;

	float LastDoorOpenTiame=0;

		
};
