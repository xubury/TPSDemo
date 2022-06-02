// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATPSCamera::ATPSCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	check(CameraComponent != nullptr);
}

// Called when the game starts or when spawned
void ATPSCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);	
	if (OurPlayerController) {
		OurPlayerController->SetViewTarget(this);
	}
}

// Called every frame
void ATPSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor) {
		FVector TargetPos = TargetActor->GetActorLocation();
		// make camera 45 degree top down while following the character
		const FRotator Rotation = FRotator(-45, 0, 0);
		FVector Pos = TargetPos - Rotation.Vector() * CameraOffset + CameraLookAtOffset;
		SetActorLocation(Pos);
		SetActorRotation(Rotation);
	}
}

