// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_IncreaseDetectionVal.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTS_IncreaseDetectionVal::UBTS_IncreaseDetectionVal()
{
	NodeName = TEXT("Increase the detection of the target");
}

void UBTS_IncreaseDetectionVal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);



	// Increase detection over time...
	// TODO: Remove this basic implementation
	float currentDetection  = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	currentDetection++;
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), currentDetection);



	// TODO: Check the distance to the actorToCHeck


	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), currentDetection);
}

FString UBTS_IncreaseDetectionVal::GetStaticDescription() const
{
	return FString::Printf(TEXT("Update the selected Blackboard Key to represent target detection ammount"));
}
