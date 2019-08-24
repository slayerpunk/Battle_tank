// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectBaseUtility.h"



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
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//TODO Should we use the tick?
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{	
	if (!ensure(Barrel)) { return; }
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
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Turret = TurretToSet; 
	Barrel = BarrelToSet;
}

void  UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DifferenceRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DifferenceRotator.Pitch); 
	Turret->Rotate(DifferenceRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && Projectile_Blueprint)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - FireTime) > ReloadTime;
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile_Blueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		FireTime = FPlatformTime::Seconds();
	}
}