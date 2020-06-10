// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateTaggedStatus.h"
#include "ParticipantAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdateTaggedStatus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	AParticipantAIController* Controller = Cast<AParticipantAIController>(OwnerComp.GetOwner());
	bool bIsTagged = false;

	if (Blackboard && Controller)
	{
		if (Controller->GetPawn()->Tags.Find(FName("Tagged")) != -1)
		{
			bIsTagged = true;
		}
	}

	Blackboard->SetValueAsBool(IsTaggedKey.SelectedKeyName, bIsTagged);
}