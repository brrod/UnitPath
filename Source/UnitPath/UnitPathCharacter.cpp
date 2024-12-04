// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnitPathCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AUnitPathCharacter::AUnitPathCharacter()
{
	// Initialize UnitCount
	UnitCount = 1;

	// Create the mesh component
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));

	// Attach the mesh component to the character's root component
	CharacterMesh->SetupAttachment(RootComponent);
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does


	//CameraBoom->TargetArmLength = 800.f; //default setting commented out
	//CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	// Adjust the length and angle of the camera boom
	CameraBoom->TargetArmLength = 700.f; // Distance from the character
	CameraBoom->SetWorldRotation(FRotator(-5.f, 0.f, 0.f)); // Angle of the camera
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Raise the camera boom higher above the character
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 100.f)); // Adjust Z value as needed
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUnitPathCharacter::MoveRight(float Value)
{
	// Add movement input along the Y-axis
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AUnitPathCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the MoveRight function to the "MoveRight" axis
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnitPathCharacter::MoveRight);
}

void AUnitPathCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// Automatic forward movement along the X-axis
	AddMovementInput(FVector(1.f, 0.f, 0.f), 1.0f);
}
