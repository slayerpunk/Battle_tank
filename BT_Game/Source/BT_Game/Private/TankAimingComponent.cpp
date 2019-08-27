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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
// 	Super::BeginPlay();
	FireTime = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Platform time = %f"), FPlatformTime::Seconds())
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

//Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{

	if((FPlatformTime::Seconds() - FireTime) < ReloadTime)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!Barrel) { return false; }	
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
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
	if (bHaveAimAt)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation();
		MoveBarrelTowards(AimDirection);
	}
}


void  UTankAimingComponent::MoveBarrelTowards(FVector tAimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = tAimDirection.Rotation();
	auto DifferenceRotator = AimAsRotator - BarrelRotator;
	
	if (DifferenceRotator.Yaw > 180)
	{
		DifferenceRotator.Yaw -= 360;
	}
	else if (DifferenceRotator.Yaw < -180)
	{
		DifferenceRotator.Yaw += 360;
	}
	
	Barrel->Elevate(DifferenceRotator.Pitch); 
	Turret->Rotate(DifferenceRotator.Yaw);
}

void UTankAimingComponent::Fire()
{	
	if (FiringStatus != EFiringStatus::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(Projectile_Blueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile_Blueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		FireTime = FPlatformTime::Seconds();
	}
}

