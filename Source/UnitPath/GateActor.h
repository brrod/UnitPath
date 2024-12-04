// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateActor.generated.h"

UENUM(BlueprintType)
enum class EGateOperation : uint8
{
	Add         UMETA(DisplayName = "+"),
	Subtract    UMETA(DisplayName = "-"),
	Multiply    UMETA(DisplayName = "x"),
	Divide      UMETA(DisplayName = "/")
};

UCLASS()
class UNITPATH_API AGateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* GateMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionComponent;

	// Gate properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	EGateOperation OperationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
	int32 OperationValue;

	// Overlap function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
