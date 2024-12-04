// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UnitPathCharacter.h"

// Sets default values
AObstacleActor::AObstacleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Collision Component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacleActor::OnOverlapBegin);

	// Mesh Component
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(RootComponent);

	// Default damage value
	DamageValue = 5;
}

// Called when the game starts or when spawned
void AObstacleActor::BeginPlay()
{
	Super::BeginPlay();
	
}
void AObstacleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									bool bFromSweep, const FHitResult& SweepResult)
{
	AUnitPathCharacter* PlayerCharacter = Cast<AUnitPathCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Reduce UnitCount
		PlayerCharacter->UnitCount -= DamageValue;

		// Clamp UnitCount to a minimum of 1
		PlayerCharacter->UnitCount = FMath::Max(PlayerCharacter->UnitCount, 1);

		// Optional: Play a damage effect

		// Destroy the obstacle if it's meant to be one-time
		// Destroy();
	}
}
// Called every frame
void AObstacleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

