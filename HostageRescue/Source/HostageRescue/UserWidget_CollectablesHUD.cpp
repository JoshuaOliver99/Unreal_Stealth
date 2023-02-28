// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_CollectablesHUD.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"

void UUserWidget_CollectablesHUD::NativeConstruct()
{
	Super::NativeConstruct();

	TimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimeText")));
	VisibilityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("VisibilityText")));
	CollectablesText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CollectablesText")));
}

void UUserWidget_CollectablesHUD::UpdateTimeText(float NewTime)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%f"), NewTime)));
	}
}

void UUserWidget_CollectablesHUD::UpdateVisibilityText(float NewVisibility)
{
	if (VisibilityText)
	{
		VisibilityText->SetText(FText::FromString(FString::Printf(TEXT("Visibility: %f"), NewVisibility)));
	}
}

void UUserWidget_CollectablesHUD::UpdateCollectablesText(int NewCollectedNum, int TotalCollectables)
{
	if (CollectablesText)
	{
		CollectablesText->SetText(FText::FromString(FString::Printf(TEXT("Collected: %i/%i"), NewCollectedNum, TotalCollectables)));
	}
}


