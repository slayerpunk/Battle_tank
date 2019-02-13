// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack * SetToLeftTrack, UTankTrack * SetToRightTrack)
{
	LeftTrack = SetToLeftTrack;
	RightTrack = SetToRightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!RightTrack || !LeftTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateRight(float Throw)
{
	if (!RightTrack || !LeftTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


