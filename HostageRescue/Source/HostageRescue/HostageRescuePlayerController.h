// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HostageRescuePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOSTAGERESCUE_API AHostageRescuePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
	
protected:
	virtual void BeginPlay() override;
	

	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;





	// ---------- UI
public:
	UUserWidget* GetHud() const { return HUD; }
	//class UUserWidget* GetLoseScreen() const {return LoseScreenClass;}
	//class UUserWidget* GetWinScreen() const {return WinScreenClass;}
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY()
	UUserWidget* HUD;
};