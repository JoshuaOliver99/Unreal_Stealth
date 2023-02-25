// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AAIControllerBase::AAIControllerBase()
{
	// Create Default Components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Behaviour Component"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize BehaviourTree
	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}



	// HARDCODED!!!!
	// TODO: Move this to be character specific
	BlackboardComponent->SetValueAsFloat("DetectionThreshold", 50.0f);
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Initialize Blackboard
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}
