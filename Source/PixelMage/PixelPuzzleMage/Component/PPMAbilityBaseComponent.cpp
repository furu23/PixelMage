// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMAbilityBaseComponent.h"

// Sets default values for this component's properties
UPPMAbilityBaseComponent::UPPMAbilityBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UPPMAbilityBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UPPMAbilityBaseComponent::Activate(AActor* instigator)
{
	if (!instigator)
		return false;

	UPPMStateComponent* StateComp = instigator->FindComponentByClass<UPPMStateComponent>();

	if (!CanActivate(instigator))
		return false;

	return true;
}

bool UPPMAbilityBaseComponent::CanActivate(AActor* instigator) const
{
	UPPMStateComponent* StateComp = instigator->FindComponentByClass<UPPMStateComponent>();

	if (!StateComp)
		return false;

	return StateComp->IsActive();
}