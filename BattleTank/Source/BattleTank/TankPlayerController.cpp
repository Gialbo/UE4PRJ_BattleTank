// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	ATank* Tank = GetControlledTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s successful possessed"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot posess the tank"));
	}
}
