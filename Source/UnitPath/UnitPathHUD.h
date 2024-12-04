// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UnitPathHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNITPATH_API AUnitPathHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	UFont* HUDFont;	
};
