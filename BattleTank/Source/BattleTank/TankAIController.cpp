// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
		return Cast<ATank>(PlayerPawn);
	else
		return nullptr;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s successful possessed by AI"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Cannot posess the tank"));
	}

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s has found the playing: %s"), *Tank->GetName(), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find playing tank"));
	}

}
