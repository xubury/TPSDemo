// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PhysicsVolume.h"

#include <limits>
#include <cmath>

struct Ray {
    FVector Origin;
    FVector Direction;
};

struct  Plane {
    FVector Normal;
    FVector Point;
};

inline bool IntersectRayPlane(const Ray &ray, const Plane &plane,
                              FVector &world)
{
    float numer = FVector::DotProduct(plane.Normal, ray.Origin) -
                  FVector::DotProduct(plane.Normal, plane.Point);
    float denom = FVector::DotProduct(plane.Normal, ray.Direction);

    // orthogonal, can't intercect
    if (std::fabs(denom) < std::numeric_limits<float>::epsilon()) {
        return false;
    }

    world = -numer / denom * ray.Direction + ray.Origin;
    return true;
}


void UShooterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, 
											  FActorComponentTickFunction* ThisTickFunc)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunc);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	// Handle mouse control rotation
	HandleRotation();

	FRotator Rotation = UpdatedComponent->GetComponentRotation();
	FRotationMatrix Transform = FRotationMatrix(Rotation);

	const FVector Input = ConsumeInputVector();
	const float ForwardValue = FVector::DotProduct(Input, Transform.GetScaledAxis(EAxis::X));
	const float RightValue = FVector::DotProduct(Input, Transform.GetScaledAxis(EAxis::Y));
	if (ForwardValue > 0.5f) {
		Movement = MovementMode::Forward;
	} else if (ForwardValue < -0.5f) {
		Movement = MovementMode::Backward;
	}

	if (RightValue > 0.5f) {
		Movement = MovementMode::Right;
	} else if (RightValue < -0.5f) {
		Movement = MovementMode::Left;
	}

	// Simulating Gravity
	const FVector Gravity(0.f, 0.f, GetGravityZ());
	FVector Adjust = NewFallVelocity(Velocity, Gravity, DeltaTime) - Velocity;
	MoveUpdatedComponent(Adjust * DeltaTime * 40.f, Rotation, true);

	FVector Delta = Input * DeltaTime * MovementSpeed;
	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	if (!Delta.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);
		if (Hit.IsValidBlockingHit()) {
			float GravityProj = FVector::DotProduct(Hit.Normal, -Gravity.GetSafeNormal());
			// 0.707 is about 60 degrees
			if (GravityProj > 0.866f) { 
				FVector Slide = ComputeSlideVector(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
				MoveUpdatedComponent(Slide, Rotation, true);
			}
		}

	}

	FVector NewLocation = UpdatedComponent->GetComponentLocation();
	Velocity = (NewLocation - OldLocation) / DeltaTime;

	UpdateComponentVelocity();
}

FVector UShooterMovementComponent::NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const
{
	FVector Result = InitialVelocity;

	if (DeltaTime > 0.f)
	{
		// Apply gravity.
		Result += Gravity * DeltaTime;

		// Don't exceed terminal velocity.
		const float TerminalLimit = FMath::Abs(UpdatedComponent->GetPhysicsVolume()->TerminalVelocity);
		if (Result.SizeSquared() > FMath::Square(TerminalLimit))
		{
			const FVector GravityDir = Gravity.GetSafeNormal();
			if ((Result | GravityDir) > TerminalLimit)
			{
				Result = FVector::PointPlaneProject(Result, FVector::ZeroVector, GravityDir) + GravityDir * TerminalLimit;
			}
		}
	}

	return Result;
}

void UShooterMovementComponent::HandleRotation()
{
	UWorld* world = GetWorld();
	FVector TargetPos = UpdatedComponent->GetComponentLocation();
	if (world) {
		FVector2D mousePos;
		world->GetGameViewport()->GetMousePosition(mousePos);

		// Consturct the mouse ray
		Ray mouseRay;
		UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0),
			mousePos, mouseRay.Origin, mouseRay.Direction);
		Plane plane;
		plane.Point = TargetPos;
		plane.Normal = FVector::UpVector;

		FVector intersectPos;
		if (IntersectRayPlane(mouseRay, plane, intersectPos))
		{
			FVector Dir = intersectPos - plane.Point;
			UpdatedComponent->SetWorldRotation(Dir.Rotation());
		}

	}

}
