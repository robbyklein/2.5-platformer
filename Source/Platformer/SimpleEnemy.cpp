// Copyright 2023. Robert Klein.


#include "SimpleEnemy.h"

#include "PlatformerCharacter.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/SphereComponent.h"

// Sets default values
ASimpleEnemy::ASimpleEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();

		
	// Get the reference to the sphere mesh
	UStaticMeshComponent* StaticMeshComponent = FindComponentByClass<UStaticMeshComponent>();

	// Add overlap event
	if (StaticMeshComponent != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("We have the mesh!"));
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &ASimpleEnemy::OnHit);
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("We no have the mesh!"));
	}
}

// Called every frame
void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimpleEnemy::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		APlatformerCharacter* PlayerCharacter = Cast<APlatformerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			PlayerCharacter->Die();
		}
	}
}



