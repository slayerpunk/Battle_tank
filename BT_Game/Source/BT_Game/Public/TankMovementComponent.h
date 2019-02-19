// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 *  Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BT_GAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* SetToLeftTrack, UTankTrack* SetToRightTrack);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendRotateRight(float Throw);
		
private:
	UTankTrack* LeftTrack;
	UTankTrack* RightTrack;

	//Called from the pathfinding logic by the AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
