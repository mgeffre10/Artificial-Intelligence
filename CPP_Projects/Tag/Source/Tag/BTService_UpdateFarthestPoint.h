// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "BTService_UpdateFarthestPoint.generated.h"

/**
 * 
 */
UCLASS()
class TAG_API UBTService_UpdateFarthestPoint : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard Keys")
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "EQS")
	class UEnvQuery* QuerySystem;

	FEnvQueryRequest QuerySystemRequest;

	class UBlackboardComponent* Blackboard;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void OnQuerySystemFinish(TSharedPtr<FEnvQueryResult> Result);
};
