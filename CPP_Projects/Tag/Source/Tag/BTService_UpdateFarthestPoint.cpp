// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateFarthestPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void UBTService_UpdateFarthestPoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard && QuerySystem)
	{
		QuerySystemRequest = FEnvQueryRequest(QuerySystem, &OwnerComp);
		QuerySystemRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UBTService_UpdateFarthestPoint::OnQuerySystemFinish);
	}
}

void UBTService_UpdateFarthestPoint::OnQuerySystemFinish(TSharedPtr<FEnvQueryResult> Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Query Finished, getting new location"));

	FVector NewLocation = Result->GetItemAsLocation(0);

	UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *NewLocation.ToString());
	Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, NewLocation);
}