// Copyright 2023. Robert Klein.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API USimpleMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float Speed = 100;
	
	UPROPERTY(EditAnywhere)
	float MaxDistance = 100;

	UPROPERTY(EditAnywhere)
	FVector MoveDirection = FVector(-1.0f, 0.0f, 0.0f);
	
	FVector InitialLocation;
	
	void SetInitialLocation();
	void Move(float DeltaTime);
};
