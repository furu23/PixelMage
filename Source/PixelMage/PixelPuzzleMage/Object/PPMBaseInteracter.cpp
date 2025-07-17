// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMBaseInteracter.h"

// Sets default values
APPMBaseInteracter::APPMBaseInteracter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ObjectAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>("Object Animation");
	SetRootComponent(ObjectAnimation);

	if (EnumHasAnyFlags(AcceptingInteract, EPPMInteractType::Simple))
	{
		ObjectAnimation->SetGenerateOverlapEvents(true);
		ObjectAnimation->SetCollisionObjectType(ECC_Pawn);
		ObjectAnimation->SetCollisionResponseToAllChannels(ECR_Ignore);
		ObjectAnimation->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	}
	ObjectAnimation->SetLooping(false);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionBox->SetupAttachment(ObjectAnimation);
}

void APPMBaseInteracter::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->SetBoxExtent(FVector::One() * BoxSize);
}

void APPMBaseInteracter::OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType)
{
	if (!bIsAnimationValid() || !EnumHasAnyFlags(AcceptingInteract, InteractType))
		return;

	if (bIsEnable)
	{
		ObjectAnimation->PlayFromStart();
	}
	else
	{
		ObjectAnimation->Reverse();
	}
	bIsEnable = !bIsEnable;
}

FORCEINLINE bool APPMBaseInteracter::bIsAnimationValid() const
{
	return ObjectAnimation->GetFlipbook() != nullptr;
}

FORCEINLINE bool APPMBaseInteracter::bIsEnabledNow() const
{
	return bIsEnable;
}