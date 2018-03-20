// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double-speed from two different input
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO prevent double-speed from two different input
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we're replacing the functionality

	FString TankName = GetOwner()->GetName();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float EffectiveSpeed = FVector::DotProduct(TankForward, AIForwardIntention);
	float RotationSpeed = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(EffectiveSpeed);
	IntendTurnRight(RotationSpeed);

	UE_LOG(LogTemp, Warning,TEXT("%s vectoring to: %s"),*TankName, *AIForwardIntention.ToString());
}
