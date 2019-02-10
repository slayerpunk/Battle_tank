// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BT_GAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Elevate(float DegreesPerSecond);
	
private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)	
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 40;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0;
	
};
