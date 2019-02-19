// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"
#include "Runtime/Core/Public/Math/Vector.h"

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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto ForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(ForwardVector, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
//	UE_LOG(LogTemp, Warning, TEXT("Tank moves to %f, %f, %f"), MoveVelocity.X, MoveVelocity.Y, MoveVelocity.Z);
}


