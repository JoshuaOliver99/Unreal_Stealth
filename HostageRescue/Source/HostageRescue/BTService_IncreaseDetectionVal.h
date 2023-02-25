// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IncreaseDetectionVal.generated.h"

/**
 * The selected BlackboardKey is intended to be a detection value float
 */
UCLASS()
class HOSTAGERESCUE_API UBTService_IncreaseDetectionVal : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_IncreaseDetectionVal();
	
	UPROPERTY(EditAnywhere, Category=Blackboard, meta = (BaseClass = "AActor"))
	struct FBlackboardKeySelector ActorToDetectBlackboardKey;
	
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;
};
