// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

UCLASS()
class UNITPATH_API AObstacleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionComponent;

	// Damage value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	int32 DamageValue;

	// Overlap function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
