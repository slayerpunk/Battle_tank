// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Tank.h>
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BT_GAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;	
	
	void BeginPlay() override;
};
