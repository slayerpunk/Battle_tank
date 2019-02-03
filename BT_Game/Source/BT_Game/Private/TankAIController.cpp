// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Game.h"
#include "Tank.h"
#include "TankAIController.h"
#include "Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledAiTank = GetControlledTank();
	if (!ControlledAiTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No tank possessed to TanKAiController"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s possessed to AiController"), *ControlledAiTank->GetName());
	}

	ATank* PlayerControlledTank = GetPlayerTank();
	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AiController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player  %s "), *PlayerControlledTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move towards the player

		//Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//TODO Fire if Ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}