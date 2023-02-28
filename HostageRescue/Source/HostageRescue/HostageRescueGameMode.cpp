// Copyright Epic Games, Inc. All Rights Reserved.

#include "HostageRescueGameMode.h"

#include "Collectable.h"
#include "HostageRescueCharacter.h"
#include "HostageRescuePlayerController.h"
#include "UserWidget_CollectablesHUD.h"
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


	// Initialize UI
	// TODO: Make this happen a few frames later to ensure dependencies are setup
	UpdateCollectablesUI();
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
		// TODO: ShowWinScreen();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Collectables Remaining: %i"), CollectablesNum - CollectablesCollectedNum);
		UpdateCollectablesUI();
	}
}

void AHostageRescueGameMode::UpdateCollectablesUI()
{
	// Update Collections UI...
	// TODO: Sort this into a function / better place
	if (GetWorld())
	{
		// Get the first player controller in the game world
		AHostageRescuePlayerController* PlayerController = Cast<AHostageRescuePlayerController>(GetWorld()->GetFirstPlayerController());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerController!"));

			UUserWidget_CollectablesHUD* CollectablesHud = Cast<UUserWidget_CollectablesHUD>(PlayerController->GetHud());

			if (CollectablesHud)
			{
				UE_LOG(LogTemp, Warning, TEXT("CollectablesHud!"));

				CollectablesHud->UpdateCollectablesText(CollectablesCollectedNum, CollectablesNum);
			}
		}
	}
}
