// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSDemoGameModeBase.h"
#include "TPSCamera.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

ATPSDemoGameModeBase::ATPSDemoGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ATPSDemoGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is TPSGameMode!"));

	ATPSCamera *Camera = GetWorld()->SpawnActor<ATPSCamera>();
	Camera->CameraOffset = CameraOffset;
	Camera->CameraLookAtOffset = CameraLookAtOffset;
	Camera->TargetActor = UGameplayStatics::GetPlayerPawn(this, 0);

	ResetEnemySpawnTimer();
}

void ATPSDemoGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemySpawnTimer -= DeltaTime;
	if (EnemySpawnTimer <= 0) {
		//TODO: random location around player
		FVector Location;
		FRotator Rotation;
		SpawnEnemy(Location, Rotation);
		ResetEnemySpawnTimer();
	}
}

void ATPSDemoGameModeBase::ResetEnemySpawnTimer()
{
	EnemySpawnTimer = TimeBetweenEnemySpawn;
}

void ATPSDemoGameModeBase::SpawnEnemy(const FVector &Location, const FRotator &Rotation)
{
	if (EnemyActor) {
		//TODO:Spawn Enemy Actor
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString::Printf(TEXT("Spawn Enemy At:(%f, %f, %f)"),
										 Location.X, Location.Y, Location.Z));
		FActorSpawnParameters Params;
		AActor *Enemy = GetWorld()->SpawnActor<AActor>(EnemyActor->GeneratedClass, Location, Rotation, Params);
	}
}
