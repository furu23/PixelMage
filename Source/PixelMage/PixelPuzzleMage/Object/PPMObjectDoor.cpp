// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMObjectDoor.h"

// Sets default values
APPMObjectDoor::APPMObjectDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AcceptingInteract |= EPPMInteractType::Lever;
}

// Called when the game starts or when spawned
void APPMObjectDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ObjectAnimation->OnFinishedPlaying.AddUniqueDynamic(this, &APPMObjectDoor::OnDoorAnimationFinished);
}

void APPMObjectDoor::OnDoorAnimationFinished()
{

}