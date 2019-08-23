// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BT_GAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> Projectile_Blueprint;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;
	
	UTankBarrel* Barrel = nullptr;
	 
	float FireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;
};
