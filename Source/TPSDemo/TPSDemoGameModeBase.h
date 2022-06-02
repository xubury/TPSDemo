// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSDemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSDEMO_API ATPSDemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	void StartPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector CameraLookAtOffset;
};
