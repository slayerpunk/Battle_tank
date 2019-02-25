// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BT_GAME_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* BarrelToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

//	UFUNCTION(BlueprintCallable, Category = Movement)
	//void UTankMovementComponent::IntendMoveForward(float Throw);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> Projectile_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f; 
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;




	UTankBarrel* Barrel = nullptr;

	

	float FireTime = 0;
};
