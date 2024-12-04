// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnitPathGameMode.h"
#include "UnitPathPlayerController.h"
#include "UnitPathCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UnitPathHUD.h"

AUnitPathGameMode::AUnitPathGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUnitPathPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_UnitPathCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//DefaultPawnClass = AUnitPathCharacter::StaticClass();

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	// Set HUD class
	HUDClass = AUnitPathHUD::StaticClass();
}