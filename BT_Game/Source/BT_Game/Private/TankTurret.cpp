// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -5, 5);
	auto Time = GetWorld()->GetTimeSeconds();
	auto RotateChange = GetWorld()->DeltaTimeSeconds * RelativeSpeed * MaxRotationSpeed;
	auto RawNewElevation = RelativeRotation.Yaw + RotateChange;

	SetRelativeRotation(FRotator(.0f, RawNewElevation, .0f));
}


