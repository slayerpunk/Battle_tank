// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;


UCLASS()
class BT_GAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();
	
	ATank();

	virtual float TakeDamage (	float DamageAmount,	struct FDamageEvent const & DamageEvent,class AController * EventInstigator, AActor * DamageCauser	) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
