// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

