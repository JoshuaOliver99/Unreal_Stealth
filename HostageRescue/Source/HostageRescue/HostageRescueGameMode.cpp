// Copyright Epic Games, Inc. All Rights Reserved.

#include "HostageRescueGameMode.h"

#include "HostageRescueCharacter.h"
#include "HostageRescuePlayerController.h"
#include "Collectables/Collectable.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UW_CollectablesHUD.h"
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
	FTimerHandle InitializeUIDelayTimerHandle;
	GetWorldTimerManager().SetTimer(InitializeUIDelayTimerHandle,this, &AHostageRescueGameMode::UpdateUI, 0.1f, false);
}

void AHostageRescueGameMode::OnCollectableBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (const ACharacter* OtherCharacter = Cast<ACharacter>(OtherComp->GetOwner()))
	{
		if (OtherCharacter->IsPlayerControlled())
		{
			CollectablesCollectedNum++;
			OverlappedComponent->GetOwner()->Destroy();

			
			UpdateCollectablesUI();
			CheckWinCondition();
		}
	}
}

void AHostageRescueGameMode::CheckWinCondition()
{
	if (CollectablesCollectedNum == CollectablesNum)
	{
		if (GetWorld() == nullptr)
		{
			return;
		}
	
		AHostageRescuePlayerController* PlayerController = Cast<AHostageRescuePlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController == nullptr)
		{
			return;
		}

		PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
	}
}


void AHostageRescueGameMode::UpdateUI() const
{
	UpdateCollectablesUI();
	// UpdateX
	// UpdateY
	// UpdateZ
}

void AHostageRescueGameMode::UpdateCollectablesUI() const
{
	if (UUW_CollectablesHUD* CollectablesHUD = GetHUD())
	{
		CollectablesHUD->UpdateCollectablesText(CollectablesCollectedNum, CollectablesNum);
	}
}

UUW_CollectablesHUD* AHostageRescueGameMode::GetHUD() const
{
	if (GetWorld() == nullptr)
	{
		return nullptr;
	}
	
	const AHostageRescuePlayerController* PlayerController = Cast<AHostageRescuePlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr)
	{
		return nullptr;
	}
	
	return Cast<UUW_CollectablesHUD>(PlayerController->GetHud());
}
