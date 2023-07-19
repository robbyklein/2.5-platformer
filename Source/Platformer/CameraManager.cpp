// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACameraManager::ACameraManager()
{
	PrimaryActorTick.bCanEverTick = true;
	CreateBoomAndCamera();
}

void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Camera never rotates so we call it once
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}

void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToFollowTarget(DeltaTime);
}

void ACameraManager::SetFollowTarget(APlatformerCharacter* NewFollowTarget)
{
	FollowTarget = NewFollowTarget;
}

void ACameraManager::CreateBoomAndCamera()
{
	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ACameraManager::MoveToFollowTarget(float DeltaTime)
{
    if (FollowTarget)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector TargetLocation = GetTargetCameraPosition();

        // Move to new location smoothly
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, CameraPanSpeed);
    	// NewLocation.Z = 100; // I i wanted to lock y position
    	
        SetActorLocation(NewLocation);
    	
    }
}

FVector ACameraManager::GetTargetCameraPosition()
{
	FVector NewLocation = FollowTarget->GetActorLocation();
	NewLocation.Y = NewLocation.Y - CameraDistance;
	return NewLocation;
}


