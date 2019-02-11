// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle %f"), *Name, Throttle);
	auto ForceApplied = Throttle * TrackMaxDrivengForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
