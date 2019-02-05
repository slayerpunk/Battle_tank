// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -2, 2);
	auto Time = GetWorld()->GetTimeSeconds();
	auto ElevationChange = GetWorld()->DeltaTimeSeconds * RelativeSpeed * MaxDegreesPerSecond;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	SetRelativeRotation(FRotator (FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation), .0f, .0f));
	 
}


