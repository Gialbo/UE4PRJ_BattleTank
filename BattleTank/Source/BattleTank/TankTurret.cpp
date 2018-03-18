// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	//Move the turret the right amount this frame
	//Given a max elevation speed , and the frame time
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Azimuth = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, Azimuth, 0));
}


