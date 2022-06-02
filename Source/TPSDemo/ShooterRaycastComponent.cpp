// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterRaycastComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UShooterRaycastComponent::UShooterRaycastComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShooterRaycastComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShooterRaycastComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UShooterRaycastComponent::CastRay(const FVector &Dir, float Length, FHitResult& Result)
{
	bool bHit = false;

	FVector Start = GetComponentLocation();
	FVector End = Start + Dir * Length;
	TArray<AActor*> ActorToIgnore;
	bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Camera),
												 false, ActorToIgnore, EDrawDebugTrace::ForDuration,Result, true);
	return bHit;
}

