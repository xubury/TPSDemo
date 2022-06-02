// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "TPSCamera.generated.h"

UCLASS()
class TPSDEMO_API ATPSCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	float CameraOffset;

	UPROPERTY(VisibleAnywhere)
	FVector CameraLookAtOffset;

	UPROPERTY(VisibleAnywhere)
	APawn* TargetActor;

};
