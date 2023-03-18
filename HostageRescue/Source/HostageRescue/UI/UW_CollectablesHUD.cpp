// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_CollectablesHUD.h"
#include "Components/TextBlock.h"

void UUW_CollectablesHUD::NativeConstruct()
{
	Super::NativeConstruct();

	TimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimeText")));
	VisibilityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("VisibilityText")));
	CollectablesText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CollectablesText")));
}

void UUW_CollectablesHUD::UpdateTimeText(float NewTime)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%f"), NewTime)));
	}
}

void UUW_CollectablesHUD::UpdateVisibilityText(float NewVisibility)
{
	if (VisibilityText)
	{
		VisibilityText->SetText(FText::FromString(FString::Printf(TEXT("Visibility: %f"), NewVisibility)));
	}
}

void UUW_CollectablesHUD::UpdateCollectablesText(int NewCollectedNum, int TotalCollectables)
{
	if (CollectablesText)
	{
		CollectablesText->SetText(FText::FromString(FString::Printf(TEXT("Collected: %i/%i"), NewCollectedNum, TotalCollectables)));
	}
}


