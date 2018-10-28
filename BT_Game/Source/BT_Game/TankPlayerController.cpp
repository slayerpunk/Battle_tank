// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankPlayerController.h"
#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerControlledTank = GetControlledTank();
	 
	if (PlayerControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessed a tank"));
	}
	else
	{		
		UE_LOG(LogTemp, Warning, TEXT("Possessing Tank is %s"), *PlayerControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation is: %s"), *HitLocation.ToString())
	}

}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenResolution = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	return true;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

