// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UnitPathCharacter.h"

// Sets default values
AGateActor::AGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Collision Component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGateActor::OnOverlapBegin);

	// Mesh Component
	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetupAttachment(RootComponent);

	// Default values
	OperationType = EGateOperation::Add;
	OperationValue = 10;
}

// Called when the game starts or when spawned
void AGateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGateActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult)
{
	AUnitPathCharacter* PlayerCharacter = Cast<AUnitPathCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		int32& UnitCount = PlayerCharacter->UnitCount;

		switch (OperationType)
		{
		case EGateOperation::Add:
			UnitCount += OperationValue;
			break;
		case EGateOperation::Subtract:
			UnitCount -= OperationValue;
			break;
		case EGateOperation::Multiply:
			UnitCount *= OperationValue;
			break;
		case EGateOperation::Divide:
			if (OperationValue != 0)
			{
				UnitCount /= OperationValue;
			}
			break;
		default:
			break;
		}

		// Clamp UnitCount to a minimum of 1
		UnitCount = FMath::Max(UnitCount, 1);

		// Optional: Play a visual or sound effect

		// Destroy the gate after activation
		Destroy();
	}
}
// Called every frame
void AGateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

