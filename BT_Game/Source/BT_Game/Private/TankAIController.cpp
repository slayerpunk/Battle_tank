// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Game.h"

#include "TankAIController.h"
#include "Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank =GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	//TODO move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	
	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//TODO Don't Fire every frame
//	ControlledTank->Fire();
	
}
