// Copyright Epic Games, Inc. All Rights Reserved.

#include "HostageRescueGameMode.h"

#include "Collectable.h"
#include "HostageRescueCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBase.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHostageRescueGameMode::AHostageRescueGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AHostageRescueGameMode::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AHostageRescueGameMode::Initialize()
{
	// Find all appropriate collection triggers
	TArray<AActor*> Collectables;
	UGameplayStatics::GetAllActorsOfClass(this, ACollectable::StaticClass(), Collectables);

	// Add delegate to the collectables
	for (int i = 0; i < Collectables.Num(); ++i)
	{
		if (UBoxComponent* BoxComponent  = Cast<UBoxComponent>(Collectables[i]->GetComponentByClass(UBoxComponent::StaticClass())))
		{
			CollectablesNum++;
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHostageRescueGameMode::OnCollectableBeginOverlap);
		}
	}
}

void AHostageRescueGameMode::OnCollectableBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (const ACharacter* OtherCharacter = Cast<ACharacter>(OtherComp->GetOwner()))
	{
		if (OtherCharacter->IsPlayerControlled())
		{
			CollectablesCollectedNum++;
			OverlappedComponent->GetOwner()->Destroy();

			CheckWinCondition();
		}
	}
}

void AHostageRescueGameMode::CheckWinCondition()
{
	if (CollectablesCollectedNum == CollectablesNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Won!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Collectables Remaining: %i"), CollectablesNum - CollectablesCollectedNum);
	}
}
