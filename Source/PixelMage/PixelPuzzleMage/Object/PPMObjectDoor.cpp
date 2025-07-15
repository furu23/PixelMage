// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMObjectDoor.h"

// Sets default values
APPMObjectDoor::APPMObjectDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>("Door Animation");
	DoorAnimation->SetLooping(false);
}

// Called when the game starts or when spawned
void APPMObjectDoor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorAnimation->OnFinishedPlaying.AddUniqueDynamic(this, &APPMObjectDoor::OnDoorAnimationFinished);
}

FORCEINLINE bool APPMObjectDoor::bIsAnimationValid() const
{
	return DoorAnimation->GetFlipbook() != nullptr;
}

void APPMObjectDoor::OnDoorAnimationFinished()
{

}

void APPMObjectDoor::OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType)
{
	if (!bIsAnimationValid() || !EnumHasAnyFlags(AcceptingInteract, InteractType))
		return;

	if (bIsEnable)
	{
		DoorAnimation->PlayFromStart();
	}
	else
	{
		DoorAnimation->Reverse();
	}
	bIsEnable = !bIsEnable;
}

FORCEINLINE bool APPMObjectDoor::bIsEnabledNow() const
{
	return bIsEnable;
}