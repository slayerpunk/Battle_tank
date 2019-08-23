// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include <Tank.h>
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BT_GAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

//	UFUNCTION(BlueprintCallable, Category = "Setup")
//	ATank* GetControlledTank() const;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float AcceptanceRadius = 3000;

};
