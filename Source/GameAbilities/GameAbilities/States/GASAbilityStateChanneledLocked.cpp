// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GameAbilities.h"

#include "../GASAbility.h"

#include "GASAbilityStateChanneledLocked.h"

UGASAbilityStateChanneledLocked::UGASAbilityStateChanneledLocked(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentCastTime = 0;
	CurrentPeriodCount = 0;
}

void UGASAbilityStateChanneledLocked::Tick(float DeltaSeconds)
{
	GetOuterAGASAbility()->CurrentCastTime += DeltaSeconds;
	CurrentCastTime += DeltaSeconds;
	if (CurrentCastTime >= GetOuterAGASAbility()->PeriodLenght
		&& GetOuterAGASAbility()->PeriodCount > CurrentPeriodCount)
	{
		CurrentCastTime = 0;
		CurrentPeriodCount += 1;
		ExecuteAbility();
	}
	else if(CurrentPeriodCount >= GetOuterAGASAbility()->PeriodCount)
	{
		GetOuterAGASAbility()->CurrentCastTime = 0;
		CurrentPeriodCount = 0;
		ChannelFinished();
	}
}
void UGASAbilityStateChanneledLocked::ChannelStarted()
{

}
void UGASAbilityStateChanneledLocked::ExecuteAbility()
{
	GetOuterAGASAbility()->ExecuteAbility();

}

void UGASAbilityStateChanneledLocked::ChannelFinished()
{
	GetOuterAGASAbility()->bIsBeingCast = false;
	GetOuterAGASAbility()->PrimaryActorTick.SetTickFunctionEnable(false);
	GetOuterAGASAbility()->GotoState(GetOuterAGASAbility()->CooldownState);
}

void UGASAbilityStateChanneledLocked::BeginState(UGASAbilityState* PrevState)
{
	GetOuterAGASAbility()->bIsBeingCast = true;
	GetOuterAGASAbility()->AbilityCastStart();
	GetOuterAGASAbility()->PrimaryActorTick.SetTickFunctionEnable(true);
}
void UGASAbilityStateChanneledLocked::EndState()
{
	GetOuterAGASAbility()->AbilityCastEnd();
}
void UGASAbilityStateChanneledLocked::BeginActionSequence()
{}
void UGASAbilityStateChanneledLocked::EndActionSequence()
{}