// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectBaseUtility.h"

 ATank::ATank()
 {
  	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 	PrimaryActorTick.bCanEverTick = false;
  }

 float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
 {
	 int32 PointDamage = FPlatformMath::RoundToInt(DamageAmount);
	 int32 ActualDamage = FMath::Clamp(PointDamage, 0, CurrentHealth);
	 CurrentHealth -= ActualDamage;

	 if (CurrentHealth <= 0) { OnDeath.Broadcast();}

	 return ActualDamage;
 }

 float ATank::GetHealthPercent()
 {
	 return (float)CurrentHealth / (float)StartingHealth;
 }

