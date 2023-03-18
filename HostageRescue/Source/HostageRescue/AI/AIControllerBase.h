// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class HOSTAGERESCUE_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()


public:
	AAIControllerBase();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;



	// TODO: Review - Perception
public:

	// Delegate Called OnPerceptionUpdated 
	//UFUNCTION()
	//void OnPerceptionRegistered(const TArray<AActor*>& UpdatedActors);
};
