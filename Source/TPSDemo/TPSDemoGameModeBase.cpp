// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSDemoGameModeBase.h"
#include "TPSCamera.h"
#include "Kismet/GameplayStatics.h"


void ATPSDemoGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is TPSGameMode!"));

	ATPSCamera *Camera = GetWorld()->SpawnActor<ATPSCamera>();
	Camera->CameraOffset = CameraOffset;
	Camera->CameraLookAtOffset = CameraLookAtOffset;
	Camera->TargetActor = UGameplayStatics::GetPlayerPawn(this, 0);
}
