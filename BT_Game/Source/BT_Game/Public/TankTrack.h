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

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void DriveTrack(float Throttle);



	//F
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivengForce = 400000;


private:
	
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySideForce();


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
