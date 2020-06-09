// Fill out your copyright notice in the Description page of Project Settings.


#include "Participant.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AParticipant::AParticipant()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(GetRootComponent());

	TriggerVolume->InitCapsuleSize(60.f, 96.f);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.f, 0.0f); // ...at this rotation rate
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bCanBeTagged = true;

	TaggedMaxWalkSpeed = 500.f;
	DefaultMaxWalkSpeed = 600.f;
}

// Called when the game starts or when spawned
void AParticipant::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AParticipant::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AParticipant::OnEndOverlap);

	if (ActorHasTag(FName("Tagged")))
	{
		GetCharacterMovement()->MaxWalkSpeed = TaggedMaxWalkSpeed;
	}
}

// Called every frame
void AParticipant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParticipant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AParticipant::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AParticipant::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AParticipant::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AParticipant::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AParticipant::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap on %s"), *GetFName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("IsTagged: %s"), ActorHasTag(FName("Tagged")) ? TEXT("TRUE") : TEXT("FALSE"));
	UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s"), *OtherActor->GetClass()->GetFName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("CanBeTagged: %s"), bCanBeTagged ? TEXT("TRUE") : TEXT("FALSE"));*/

	if (ActorHasTag(FName("Tagged")) && Cast<AParticipant>(OtherActor) && bCanBeTagged)
	{
		AParticipant* TargetParticipant = Cast<AParticipant>(OtherActor);

		bCanBeTagged = false;
		TargetParticipant->bCanBeTagged = false;

		UE_LOG(LogTemp, Warning, TEXT("Transferring 'Tagged' tag from %s to %s"), *GetFName().ToString(), *TargetParticipant->GetFName().ToString());

		Tags.Remove(FName("Tagged"));
		TargetParticipant->Tags.Add(FName("Tagged"));
		UE_LOG(LogTemp, Warning, TEXT("Participant got Tagged, waiting for overlap to end."));

		GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
		TargetParticipant->GetCharacterMovement()->MaxWalkSpeed = TaggedMaxWalkSpeed;
	}
}

void AParticipant::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*UE_LOG(LogTemp, Warning, TEXT("OnEndOverlap on %s"), *GetFName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Hit Participant: %s"), *OtherActor->GetClass()->GetFName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("CanBeTagged: %s"), bCanBeTagged ? TEXT("TRUE") : TEXT("FALSE"));*/

	if (Cast<AParticipant>(OtherActor) && !bCanBeTagged)
	{
		AParticipant* TargetParticipant = Cast<AParticipant>(OtherActor);

		bCanBeTagged = true;
		TargetParticipant->bCanBeTagged = true;

		UE_LOG(LogTemp, Warning, TEXT("Overlap ended, enabling ability to tag another player."));
	}
}