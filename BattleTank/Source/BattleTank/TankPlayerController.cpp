// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		//Subscribe to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
	}
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn()) { return; } // if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);
	if (bGotHitLocation)//Side effect, is going to line trace
	{
		//Tell the controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(
		(float)ViewportSizeX*CrossHairXLocation,
		(float)ViewportSizeY*CrossHairYLocation
	);
	
	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line trace along that direction, and see what we hit (up to a max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;//To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const 
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	} 
}

void ATankPlayerController::OnPlayerTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player tank died"));
	StartSpectatingOnly();
}
