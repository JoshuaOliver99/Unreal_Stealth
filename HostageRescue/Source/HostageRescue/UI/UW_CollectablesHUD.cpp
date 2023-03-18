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

void UUW_CollectablesHUD::UpdateTimeText(const float NewTime)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%f"), NewTime)));
	}
}

void UUW_CollectablesHUD::UpdateVisibilityText(const float NewVisibility)
{
	if (VisibilityText)
	{
		VisibilityText->SetText(FText::FromString(FString::Printf(TEXT("Visibility: %f"), NewVisibility)));
	}
}

void UUW_CollectablesHUD::UpdateCollectablesText(const int NewCollectedNum, const int TotalCollectables)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateCollectablesText"));

	if (CollectablesText)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollectablesText"));

		CollectablesText->SetText(FText::FromString(FString::Printf(TEXT("Collected: %i/%i"), NewCollectedNum, TotalCollectables)));
	}
}


