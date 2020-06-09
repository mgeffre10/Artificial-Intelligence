// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Participant.h"
#include "AIParticipant.generated.h"

/**
 * 
 */
UCLASS()
class TAG_API AAIParticipant : public AParticipant
{
	GENERATED_BODY()

public:

	AAIParticipant();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
