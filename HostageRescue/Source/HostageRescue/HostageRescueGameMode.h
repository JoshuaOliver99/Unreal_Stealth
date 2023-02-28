// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HostageRescueGameMode.generated.h"

UCLASS(minimalapi)
class AHostageRescueGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHostageRescueGameMode();
	
	
	
	// TODO: ----- Review
	
// ----- Initialization
	
	virtual void BeginPlay() override;
	
	// Initializes the starting values
	void Initialize();

// ----- Collectables

	UPROPERTY(VisibleAnywhere)
	int CollectablesNum;

	UPROPERTY(VisibleAnywhere)
	int CollectablesCollectedNum;
	
	// Delegate for ACollectables OnComponentBeginOverlap. Intended for checking player collisions
	UFUNCTION()
	void OnCollectableBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

// ----- Win / Loss
	
	void CheckWinCondition();

	// TODO
	//void CheckLoseCondition();

// ----- UI

	void UpdateCollectablesUI();
};



