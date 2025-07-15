// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMObjectLever.h"

// Sets default values
APPMObjectLever::APPMObjectLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LeverAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>("LeverAnimation");
}

void APPMObjectLever::BeginPlay()
{
	LeverAnimation->OnFinishedPlaying.AddUniqueDynamic(this, &APPMObjectLever::OnLeverAnimationFinished);
}

FORCEINLINE bool APPMObjectLever::bIsAnimationValid() const
{
	return LeverAnimation->GetFlipbook() != nullptr;
}

void APPMObjectLever::OnLeverAnimationFinished()
{
	IPPMInteractable* TargetInteractor = Cast<IPPMInteractable>(TargetActor);
	if (!TargetInteractor)
		return;

	TargetInteractor->Execute_OnInteract(this, Cast<AActor>(this), EPPMInteractType::Lever);
}

void APPMObjectLever::OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType)
{
	if (ensure(!bIsAnimationValid() || !EnumHasAnyFlags(AcceptingInteract, InteractType)))
		return;

	if (bIsEnable)
	{
		LeverAnimation->Play();
	}
	else
	{
		LeverAnimation->Reverse();
	}
	bIsEnable = !bIsEnable;
}

FORCEINLINE bool APPMObjectLever::bIsEnabledNow() const
{
	return bIsEnable;
}