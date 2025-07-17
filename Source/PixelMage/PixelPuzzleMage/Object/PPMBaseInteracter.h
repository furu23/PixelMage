// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Interface/PPMInteractable.h"

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

#include "PPMBaseInteracter.generated.h"

/*
* this is basic Implementation and properties of Interactor abstract class
* for using it, inherit this class and make the way that handle event dispatch or delegate
* Simple Example is PPMObjectLever.cpp
*/

UCLASS(Abstract)
class PIXELMAGE_API APPMBaseInteracter : public AActor, public IPPMInteractable
{
	GENERATED_BODY()

public:
	APPMBaseInteracter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PPM Object", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* ObjectAnimation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PPM Object", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox = nullptr;

	// Actor that Activate to Other Actor, it indicate to other actor (Blueprint Need)
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PPM Object", meta = (AllowPrivateAccess = "true"))
	AActor* TargetActor = nullptr;

	// Accepting Type of Interact 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PPM Object", meta = (AllowPrivateAccess = "true", Bitmask))
	EPPMInteractType AcceptingInteract = EPPMInteractType::None;

	// Collision Box Size, n * 12 - 0.5 recommend
	UPROPERTY(EditAnywhere, Category = "PPM Object", meta = (AllowPrivateAccess = "true"))
	float BoxSize = 7.5f;

	FORCEINLINE bool bIsAnimationValid() const;

	// Bool Variable for clarify
	bool bIsEnable = false;

protected:
	// Interact Implementation, Compare InteractType and AccpetingInteract
	virtual void OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType) override;

public:
	// API for finding out enable
	FORCEINLINE bool bIsEnabledNow() const;
};
