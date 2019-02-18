// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BT_GAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* SetToLeftTrack, UTankTrack* SetToRightTrack);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendRotateRight(float Throw);

	//TODO check best protection
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:
	UTankTrack* LeftTrack;
	UTankTrack* RightTrack;
};
