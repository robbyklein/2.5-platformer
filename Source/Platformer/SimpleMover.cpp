// Copyright 2023. Robert Klein.


#include "SimpleMover.h"

USimpleMover::USimpleMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USimpleMover::BeginPlay()
{
	Super::BeginPlay();

	// Store initial location for moving back and forth
	SetInitialLocation();
}


void USimpleMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Move the actor
	Move(DeltaTime);
}

void USimpleMover::Move(float DeltaTime)
{
	// Get the actor we're moving
	AActor* Actor = GetOwner();
	
	// Calculate new location
	FVector CurrentLocation = Actor->GetActorLocation();
	FVector TargetLocation = CurrentLocation + MoveDirection * (Speed * DeltaTime);

	// Reverse if at end of the line
	if (FVector::Dist(TargetLocation, InitialLocation) > MaxDistance)
	{
		MoveDirection *= -1.0f; // reverse direction
		TargetLocation = Actor->GetActorLocation() + MoveDirection * (Speed * DeltaTime); // recalculate new location
	}
	
	// Set actor's new location
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, 5);
	Actor->SetActorLocation(NewLocation);

}

void USimpleMover::SetInitialLocation() 
{
	AActor* Actor = GetOwner();
	InitialLocation = Actor->GetActorLocation();
	
}



