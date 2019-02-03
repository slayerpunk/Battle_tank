// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Game.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

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
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector CameraWorldLocation, LookDirection;	
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
if(GetLookDirection(ScreenLocation, LookDirection))
{
	if (GetLookVectorHitLocation(LookDirection, OUT HitLocation))
	{
		return true;
	}
}
return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection*LineTraceRange;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	if (
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility,
			TraceParameters,
			FCollisionResponseParams()
		)
	)
	{
		HitLocation = HitResult.Location;
	}	
	else
	{
		HitLocation = FVector(0, 0, 0);
	}
	return HitResult.IsValidBlockingHit();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

