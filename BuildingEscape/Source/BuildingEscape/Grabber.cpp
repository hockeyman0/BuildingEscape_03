// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
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

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation, 
        OUT PlayerViewPointRotation
    );
    UE_LOG(LogTemp, Warning, TEXT("Location: (%s), Rotation: (%s)"), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.GetNormalized().ToString()));
    //UE_LOG(LogTemp, Warning, TEXT("VECTOR: (%s)"), *(PlayerViewPointRotation.GetNormalized().Vector().ToString()));
    // ray-cast out to reach distance
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.GetNormalized().Vector() * Reach;
    //FVector LineTraceEnd = PlayerViewPointLocation + FVector(Player)
    // see what we hit
    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation,
        LineTraceEnd,
        FColor(255, 0, 0),
        false,
        0.f,
        0,
        10.f
    );
    //PlayerViewPointRotation.
    // press f to pay respect
}

