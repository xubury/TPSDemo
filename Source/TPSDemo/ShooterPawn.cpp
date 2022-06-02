// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPawn.h"


// Sets default values
AShooterPawn::AShooterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	check(CapsuleComponent != nullptr);
	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	check(MeshComponent != nullptr);
	MeshComponent->SetupAttachment(RootComponent);


	MovementComponent = CreateDefaultSubobject<UShooterMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShooterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterPawn::MoveRight);
}

void AShooterPawn::MoveRight(float Value)
{
	FVector Direction = GetActorRightVector();

	if (MovementComponent) {
		MovementComponent->AddInputVector(Direction * Value);
	}
}


void AShooterPawn::MoveForward(float Value)
{
	FVector Direction = GetActorForwardVector();

	if (MovementComponent) {
		MovementComponent->AddInputVector(Direction * Value);
	}
}

