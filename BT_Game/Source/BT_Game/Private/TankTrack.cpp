// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Game.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack(CurrentThrottle);
	ApplySideForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySideForce()
{
	auto SlipperySpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	// 	if (SlipperySpeed > 100.0)
	// 	{
	// 		SlipperySpeed = 100.0;
	// 	}
	// 	else if (SlipperySpeed < -100.0)
	// 	{
	// 		SlipperySpeed = -100.0;
	// 	}
	auto CorrectAcceleration = -SlipperySpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2;				//Two tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{	
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1);
}

void UTankTrack::DriveTrack(float Throttle)
{
	auto ForceApplied = Throttle * TrackMaxDrivengForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

