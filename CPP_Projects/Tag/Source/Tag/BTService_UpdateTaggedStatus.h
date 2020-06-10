// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateTaggedStatus.generated.h"

/**
 * 
 */
UCLASS()
class TAG_API UBTService_UpdateTaggedStatus : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard Keys")
	FBlackboardKeySelector IsTaggedKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
