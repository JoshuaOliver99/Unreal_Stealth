// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_FloatConditionCheck.generated.h"

UENUM(BlueprintType)
enum class ComparisonTypes : uint8
{
	LessThan,
	MoreThan,
	Equal
};

/**
 * 
 */
UCLASS()
class HOSTAGERESCUE_API UBTD_FloatConditionCheck : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTD_FloatConditionCheck();
	
	UPROPERTY(EditAnywhere, Category = "Comparison")
	ComparisonTypes ComparisonType;

	UPROPERTY(EditAnywhere, Category = "Comparison")
	float ValueToCompareTo;

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;

};
