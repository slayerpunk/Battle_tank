// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//TODO Should we use the tick?
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimAt = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,  
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimAt)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		//No aim solution found
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	
	Turret = TurretToSet;
}

void  UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DifferenceRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DifferenceRotator.Pitch); 
	Turret->Rotate(DifferenceRotator.Yaw);
}