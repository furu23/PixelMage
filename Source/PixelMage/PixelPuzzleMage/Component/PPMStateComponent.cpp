// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMStateComponent.h"

// Sets default values for this component's properties
UPPMStateComponent::UPPMStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CurrentState = EPPMCharacterState::Idle; // After, Stating Set
}

// Called when the game starts
void UPPMStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPPMStateComponent::SetState(EPPMCharacterState NewState)
{
	if (NewState == CurrentState)
		return;

	FPPMStateTransition* AllowStateSet = AllowState.Find(CurrentState);
	if (AllowStateSet)
	{
		if (AllowStateSet->ValidTransitionSet.Contains(NewState))
		{
			OnChangeState.Broadcast(NewState);
			CurrentState = NewState;
		}
	}
	else
	{
		// Error Handling Logic Here
	}
}

FORCEINLINE EPPMCharacterState UPPMStateComponent::GetCurrentState() const
{
	return CurrentState;
}

void UPPMStateComponent::SetNewAllowState(EPPMCharacterState TargetState, EPPMCharacterState NewAllowState)
{
	FPPMStateTransition* AllowStateSet =  AllowState.Find(TargetState);

	if (AllowStateSet)
	{
		if (!AllowStateSet->ValidTransitionSet.Contains(NewAllowState))
			AllowStateSet->ValidTransitionSet.Add(NewAllowState);
	}
	else
	{
		// Error Handling Logic Here
	}
}

FORCEINLINE bool UPPMStateComponent::IsInAllowState(EPPMCharacterState QueryState)
{
	FPPMStateTransition* AllowStateSet = AllowState.Find(CurrentState);

	return AllowStateSet->ValidTransitionSet.Contains(QueryState);
}

