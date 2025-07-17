// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMObjectLever.h"

// Sets default values
APPMObjectLever::APPMObjectLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void APPMObjectLever::BeginPlay()
{
	Super::BeginPlay();

	ObjectAnimation->OnFinishedPlaying.AddUniqueDynamic(this, &APPMObjectLever::OnLeverAnimationFinished);
}

void APPMObjectLever::OnLeverAnimationFinished()
{
	IPPMInteractable* TargetInteractor = Cast<IPPMInteractable>(TargetActor);
	if (!TargetInteractor)
		return;

	TargetInteractor->Execute_OnInteract(Cast<UObject>(TargetInteractor), Cast<AActor>(this), EPPMInteractType::Lever);
}