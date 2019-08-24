// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectBaseUtility.h"


// void ATank::Fire()
// {
// 	if (!ensure(Barrel)) { return; }
// 	bool isReloaded = (FPlatformTime::Seconds() - FireTime) > ReloadTime;
// 	if (isReloaded) {
// 		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
// 			Projectile_Blueprint,
// 			Barrel->GetSocketLocation(FName("Projectile")),
// 			Barrel->GetSocketRotation(FName("Projectile"))
// 			);
// 		Projectile->LaunchProjectile(LaunchSpeed);
// 		FireTime = FPlatformTime::Seconds();
// 	}
// }

// void ATank::BeginPlay()
// {
// 	Super::BeginPlay();
// }
// 
// // Sets default values
 ATank::ATank()
 {
  	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 	PrimaryActorTick.bCanEverTick = false;
  }
