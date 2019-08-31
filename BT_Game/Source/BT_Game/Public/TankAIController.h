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

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


};
