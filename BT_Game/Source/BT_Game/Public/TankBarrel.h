// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hideCategories = ("Tags"))
class BT_GAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Max Speed Elevation +-1 degree per second
	void Elevate(float RelativeSpeed);
	
private:

	UPROPERTY(EditAnywhere, Category = Setup)	
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;
	
};
