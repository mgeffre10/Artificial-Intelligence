// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ParticipantAIController.generated.h"

/**
 * 
 */
UCLASS()
class TAG_API AParticipantAIController : public AAIController
{
	GENERATED_BODY()
	

public:

	AParticipantAIController();

	void OnPossess(APawn* InPawn) override;
};
