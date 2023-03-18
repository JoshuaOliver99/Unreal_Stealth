// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_CollectablesHUD.generated.h"

/**
 * 
 */
UCLASS()
class HOSTAGERESCUE_API UUW_CollectablesHUD : public UUserWidget
{
	GENERATED_BODY()

	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateTimeText(float NewTime);
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateVisibilityText(float NewVisibility);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateCollectablesText(int NewCollectedNum, int TotalCollectables);

private:
	class UTextBlock* TimeText;
	
	class UTextBlock* VisibilityText;

	class UTextBlock* CollectablesText;
};