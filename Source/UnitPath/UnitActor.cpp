// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UnitPathCharacter.h"

// Sets default values
AUnitActor::AUnitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Collision Component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AUnitActor::OnOverlapBegin);

	// Mesh Component
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	UnitMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUnitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult)
{
	AUnitPathCharacter* PlayerCharacter = Cast<AUnitPathCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Increase the UnitCount
		PlayerCharacter->UnitCount++;

		// Optional: Play a sound or visual effect

		// Destroy the unit actor
		Destroy();
	}
}
// Called every frame
void AUnitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

