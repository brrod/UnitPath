// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitPathHUD.h"
#include "Engine/Canvas.h"
#include "UnitPathCharacter.h"

void AUnitPathHUD::DrawHUD()
{
	Super::DrawHUD();

	AUnitPathCharacter* PlayerCharacter = Cast<AUnitPathCharacter>(GetOwningPawn());
	if (PlayerCharacter && HUDFont)
	{
		FString UnitCountText = FString::Printf(TEXT("Units: %d"), PlayerCharacter->UnitCount);

		// Set text parameters
		FCanvasTextItem TextItem(FVector2D(50.f, 50.f), FText::FromString(UnitCountText), HUDFont, FLinearColor::White);

		// Draw the text
		Canvas->DrawItem(TextItem);
	}
}