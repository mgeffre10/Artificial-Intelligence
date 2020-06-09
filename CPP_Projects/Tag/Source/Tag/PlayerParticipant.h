// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Participant.h"
#include "PlayerParticipant.generated.h"

/**
 * 
 */
UCLASS()
class TAG_API APlayerParticipant : public AParticipant
{
	GENERATED_BODY()

public:

	APlayerParticipant();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FollowCamera;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
