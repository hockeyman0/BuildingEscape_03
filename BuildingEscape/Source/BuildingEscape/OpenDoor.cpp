// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    Owner = GetOwner();

}

void UOpenDoor::OpenDoor()
{
    // Set the door rotation
    Owner->SetActorRotation(FRotator(0.0f, (90.0f - OpenAngle), 0.0f));
}
void UOpenDoor::CloseDoor()
{
    // Set the door rotation
    Owner->SetActorRotation(FRotator(0.0f, (90.0f - 0), 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }

    // Check if it's time to close the door
    if (LastDoorOpenTime != -1.0 && (GetWorld()->GetTimeSeconds() - LastDoorOpenTime) > DoorCloseDelay) {
        CloseDoor();
        LastDoorOpenTime = -1.0;
    }
}

