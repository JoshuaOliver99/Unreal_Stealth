// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HostageRescueGameMode.generated.h"

class UUW_CollectablesHUD;

UCLASS(minimalapi)
class AHostageRescueGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHostageRescueGameMode();
	
private:	
	virtual void BeginPlay() override;
	
	void Initialize();

	
// ----- Collectables
private:
	UPROPERTY(VisibleAnywhere)
	int CollectablesNum;

	UPROPERTY(VisibleAnywhere)
	int CollectablesCollectedNum;
	
	// Delegate for ACollectables OnComponentBeginOverlap. Intended for checking player collisions
	UFUNCTION()
	void OnCollectableBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	
// ----- Win / Loss
private:
	void CheckWinCondition();

	// TODO
	//void CheckLoseCondition();

	
// ----- UI
private:
	
	void UpdateUI() const;
	
	void UpdateCollectablesUI() const;

	UUW_CollectablesHUD* GetHUD() const;
};



