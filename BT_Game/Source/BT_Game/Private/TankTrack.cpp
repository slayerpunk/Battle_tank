// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle %f"), *Name, Throttle);
}
