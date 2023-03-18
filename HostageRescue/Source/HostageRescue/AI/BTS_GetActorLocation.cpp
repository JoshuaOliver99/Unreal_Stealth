// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_GetActorLocation.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTS_GetActorLocation::UBTS_GetActorLocation()
{
	NodeName = TEXT("Get The Location of Provided Actor");
}

void UBTS_GetActorLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	// Check that the ActorBlackboardKey is of type AActor
	const AActor* Actor = Cast<AActor>( OwnerComp.GetBlackboardComponent()->GetValueAsObject(ActorBlackboardKey.SelectedKeyName));
	if (Actor == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Actor->GetActorLocation());
}

FString UBTS_GetActorLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Sets the Blackboard Key to the location of the provided Actor"));
}
