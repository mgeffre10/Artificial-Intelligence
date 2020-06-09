// Fill out your copyright notice in the Description page of Project Settings.


#include "AIParticipant.h"
#include "ParticipantAIController.h"

AAIParticipant::AAIParticipant()
{
	//bCanBeTagged = true;

	AIControllerClass = AParticipantAIController::StaticClass();
}

void AAIParticipant::BeginPlay()
{
	Super::BeginPlay();
}