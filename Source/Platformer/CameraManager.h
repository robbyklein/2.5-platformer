// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformerCharacter.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

UCLASS()
class PLATFORMER_API ACameraManager : public AActor
{
	GENERATED_BODY()

	// Camera boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:	
	ACameraManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetFollowTarget(APlatformerCharacter* NewFollowTarget);

private:
	int32 CameraDistance = 200;
	float CameraPanSpeed = 5;
	void CreateBoomAndCamera();
	void MoveToFollowTarget(float DeltaTime);
	FVector GetTargetCameraPosition();
	APlatformerCharacter* FollowTarget;
};
