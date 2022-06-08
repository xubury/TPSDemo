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
	ATPSDemoGameModeBase();

	void StartPlay() override;

	void Tick(float DeltaTime) override;

	void ResetEnemySpawnTimer();

	void SpawnEnemy(const FVector &Location, const FRotator &Rotation);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector CameraLookAtOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawn)
	float TimeBetweenEnemySpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemySpawn)
	float EnemySpawnTimer;

	UPROPERTY(EditAnywhere, Category = EnemySpawn)
	UBlueprint* EnemyActor;
};
