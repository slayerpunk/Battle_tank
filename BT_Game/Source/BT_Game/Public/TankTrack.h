// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/** 
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BT_GAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = input)
	void SetThrottle(float Throttle);
	
	
};
