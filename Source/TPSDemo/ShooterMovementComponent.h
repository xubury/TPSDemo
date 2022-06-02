// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ShooterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class MovementMode : uint8 {
	None UMETA(DisplayName = "None"),
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Falling UMETA(DisplayName = "Falling"),
};

/**
 * 
 */
UCLASS()
class TPSDEMO_API UShooterMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, 
					   FActorComponentTickFunction* ThisTickFunc) override;

	FVector NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const;

	void HandleRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MovementSpeed{ 10.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	MovementMode Movement{ MovementMode::None };

};
