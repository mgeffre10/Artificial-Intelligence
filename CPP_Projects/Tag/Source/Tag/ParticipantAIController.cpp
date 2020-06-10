// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticipantAIController.h"
#include "AIParticipant.h"

AParticipantAIController::AParticipantAIController()
{

}

void AParticipantAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAIParticipant* AIParticipant = Cast<AAIParticipant>(InPawn);

	if (AIParticipant)
	{
		UBehaviorTree* BehaviorTree = AIParticipant->BehaviorTree;

		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);
		}
	}
}
