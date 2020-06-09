// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Participant.generated.h"

UCLASS()
class TAG_API AParticipant : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParticipant();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	class UCapsuleComponent* TriggerVolume;

	bool bCanBeTagged;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TaggedMaxWalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DefaultMaxWalkSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
