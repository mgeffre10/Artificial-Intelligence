// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindClosestPlayer.h"
#include "AIParticipant.h"
#include "ParticipantAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EngineUtils.h"

void UBTService_FindClosestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get Blackboard
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	// Get AI
	AParticipantAIController* Controller = Cast<AParticipantAIController>(OwnerComp.GetOwner());

	AAIParticipant* OwningAIParticipant = Cast<AAIParticipant>(Controller->GetPawn());

	if (!Blackboard || !Controller || !OwningAIParticipant)
	{
		return;
	}

	float MinDistance = -1.f;
	AParticipant* ClosestActor = nullptr;

	for (TActorIterator<AParticipant> ParticipantIter(GetWorld()); ParticipantIter; ++ParticipantIter)
	{
		if (OwningAIParticipant == *ParticipantIter)
		{
			continue;
		}

		float Distance = (ParticipantIter->GetActorLocation() - OwningAIParticipant->GetActorLocation()).Size();

		if (MinDistance == -1.f || Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestActor = *ParticipantIter;
		}
	}

	Blackboard->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestActor);
	UE_LOG(LogTemp, Warning, TEXT("ClosestActor: %s"), *ClosestActor->GetFName().ToString());
	return;
}