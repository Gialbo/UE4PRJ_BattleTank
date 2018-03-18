// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

//Move the barrel the right amount this frame
//Given a max elevation speed. and the frame time
void UTankBarrel::Elevate(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	//Move the barrel the right amount this frame
	//Given a max elevation speed , and the frame time
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);

	
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


