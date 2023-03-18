// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_ClosestPerceivedTarget.generated.h"

/**
 * Required the AI to have the perception component with sight enabled
 */
UCLASS()
class HOSTAGERESCUE_API UBTS_ClosestPerceivedTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_ClosestPerceivedTarget();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;

};
