// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindRandomLocation::UBTT_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	// Accept only vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get AI Pawn
	AAIController* AIController{OwnerComp.GetAIOwner()};
	const APawn* AIPawn{AIController->GetPawn()};

	// Get Pawn Origin
	const FVector Origin{AIPawn->GetActorLocation()};

	// Obtain Navigation System and find a random location
	const UNavigationSystemV1* NavSystem{UNavigationSystemV1::GetCurrent(GetWorld())};
	//if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	if (IsValid(NavSystem) && NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// Signal the BehaviourTreeComponent that the task finished with a success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}

FString UBTT_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Find Reachable Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
