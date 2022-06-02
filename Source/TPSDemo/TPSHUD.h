// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "TPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class TPSDEMO_API ATPSHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CursorTexture;
	
};
