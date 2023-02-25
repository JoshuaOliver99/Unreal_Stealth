// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_FloatConditionCheck.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_FloatConditionCheck::UBTDecorator_FloatConditionCheck()
{
	NodeName = TEXT("Float Conditional Check");

	// Accept only floats
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_FloatConditionCheck, BlackboardKey));
}

bool UBTDecorator_FloatConditionCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const float SelectedKeyValue  = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	
	switch (ComparisonType)
	{
	case ComparisonTypes::LessThan:
		if (SelectedKeyValue < ValueToCompareTo)
			return true;
		break;
	case ComparisonTypes::MoreThan:
		if (SelectedKeyValue > ValueToCompareTo)
			return true;
		break;
	case ComparisonTypes::Equal:
		if (SelectedKeyValue == ValueToCompareTo)
			return true;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown option selected in ComparisonType"));
		break;
	}

	return false;
}

FString UBTDecorator_FloatConditionCheck::GetStaticDescription() const
{
	return FString::Printf(TEXT("Compare the selected Blackboard float against ValueToCompareTo"));
}
