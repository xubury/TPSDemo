// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalmeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ShooterMovementComponent.h"
#include "ShooterRaycastComponent.h"
#include "ShooterPawn.generated.h"


UCLASS()
class TPSDEMO_API AShooterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShooterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override 
	{
		return MovementComponent;
	}

	void MoveRight(float Value);

	void MoveForward(float Value);

	void Shoot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	UShooterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UShooterRaycastComponent* RaycastComponent;
};
