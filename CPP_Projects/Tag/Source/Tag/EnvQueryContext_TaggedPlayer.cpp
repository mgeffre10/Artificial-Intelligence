// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_TaggedPlayer.h"
#include "Participant.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EngineUtils.h"

void UEnvQueryContext_TaggedPlayer::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AParticipant* TaggedPlayer = nullptr;

	for (TActorIterator<AParticipant> ParticipantIter(GetWorld()); ParticipantIter; ++ParticipantIter)
	{
		if (ParticipantIter->Tags.Find(FName("Tagged")) != -1)
		{
			TaggedPlayer = *ParticipantIter;
		}
	}

	if (TaggedPlayer)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, TaggedPlayer);
	}
}
