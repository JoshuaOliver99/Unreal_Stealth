// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ClosestTargetInSight.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

UBTService_ClosestTargetInSight::UBTService_ClosestTargetInSight()
{
	NodeName = TEXT("Get Closest Target in Sight");

	// Accept only Actors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_ClosestTargetInSight, BlackboardKey), AActor::StaticClass());
}

void UBTService_ClosestTargetInSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTService_ClosestTargetInSight: OwnerComp.GetAIOwner() == null "))
		return;
	}

	const UAIPerceptionComponent* OwnerPerceptionComponent = OwnerComp.GetAIOwner()->PerceptionComponent;
	if (OwnerPerceptionComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTService_ClosestTargetInSight: OwnerPerceptionComponent == null "))
		return;
	}

	// TODO
	//if (no sight component) return;
	
	TArray<AActor*> PerceivedActors;
	OwnerPerceptionComponent->GetCurrentlyPerceivedActors(UAIPerceptionComponent::StaticClass() , PerceivedActors);
	if (PerceivedActors.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTService_ClosestTargetInSight: No perceived Actors"));
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}
	
	// Find the closest actor
	AActor* ClosestActor = PerceivedActors[0];
	if (PerceivedActors.Num() > 1)
	{
		for (int i = 0; i < PerceivedActors.Num(); ++i)
		{
			// TODO: Implement a distance check for each actor. 
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), ClosestActor);
}

FString UBTService_ClosestTargetInSight::GetStaticDescription() const
{
	return FString::Printf(TEXT("Sets the Blackboard Key to the closest Actor in sight"));
}
