// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsParticipantTagged.h"
#include "AIParticipant.h"
#include "ParticipantAIController.h"

bool UBTDecorator_IsParticipantTagged::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AParticipantAIController* AIController = Cast<AParticipantAIController>(OwnerComp.GetOwner());

	AParticipant* AIParticipant = Cast<AParticipant>(AIController->GetPawn());

	if (AIParticipant && AIParticipant->Tags.Find(FName("Tagged")) != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is tagged."), *AIParticipant->GetFName().ToString());
		return true;
	}

	return false;
}