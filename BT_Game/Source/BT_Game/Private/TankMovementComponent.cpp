// Copyright Brosalin Stanislav

#include "BT_Game.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"
#include "Runtime/Core/Public/Math/Vector.h"

void UTankMovementComponent::Initialise(UTankTrack * SetToLeftTrack, UTankTrack * SetToRightTrack)
{
	LeftTrack = SetToLeftTrack;
	RightTrack = SetToRightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendRotateRight(RightThrow.Z);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(RightTrack && LeftTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateRight(float Throw)
{
	if (!ensure(RightTrack && LeftTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
