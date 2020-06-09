// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticipantAIController.h"
#include "AIParticipant.h"

AParticipantAIController::AParticipantAIController()
{

}

void AParticipantAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Called"));

	AAIParticipant* AIParticipant = Cast<AAIParticipant>(InPawn);

	if (AIParticipant)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn is AIParticipant"));
		UBehaviorTree* BehaviorTree = AIParticipant->BehaviorTree;

		if (BehaviorTree)
		{
			UE_LOG(LogTemp, Warning, TEXT("Behavior Tree is present"));
			RunBehaviorTree(BehaviorTree);
		}
	}
}
