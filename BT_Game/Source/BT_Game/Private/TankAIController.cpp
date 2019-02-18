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
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!PlayerTank || !ControlledTank) { return; }
	
	//TODO move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);


	//Aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	//TODO Don't Fire every frame
	ControlledTank->Fire();
	
}
