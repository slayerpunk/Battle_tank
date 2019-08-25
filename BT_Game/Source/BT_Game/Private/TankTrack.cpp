// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super::TickComponent();
	//TODO Check all speeds
	auto SlipperySpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	UE_LOG(LogTemp, Warning, TEXT("%s: Right Vector = %f, %f, %f"),*GetName(),GetRightVector().X, GetRightVector().Y, GetRightVector().Z)
	UE_LOG(LogTemp, Warning, TEXT("%s: Velocity = %f, %f, %f"), *GetName(), GetComponentVelocity().X, GetComponentVelocity().Y, GetComponentVelocity().Z)
	UE_LOG(LogTemp, Warning, TEXT("%s: SlipperySpeed = %f"), *GetName(), SlipperySpeed)
	if (SlipperySpeed > 100.0)
	{
		SlipperySpeed = 100.0;
	}
	else if (SlipperySpeed < -100.0)
	{
		SlipperySpeed = -100.0;
	}
	auto CorrectAcceleration = -SlipperySpeed/ DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2;				//Two tracks
	TankRoot->AddForce(CorrectionForce);

}


void UTankTrack::SetThrottle(float Throttle)
{
	
	auto ForceApplied = Throttle * TrackMaxDrivengForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
