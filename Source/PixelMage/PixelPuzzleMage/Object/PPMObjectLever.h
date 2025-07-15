// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Interface/PPMInteractable.h"
#include "../Data/PPMDataType.h"

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PPMObjectLever.generated.h"

UCLASS()
class PIXELMAGE_API APPMObjectLever : public AActor, public IPPMInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPMObjectLever();

protected:
	virtual void BeginPlay() override;

private:
	// Lever Flipbook Component, make unconfirm of checkbox in Editor, *Looping*
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PPM Lever", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* LeverAnimation = nullptr;

	// Actor that Activate to Lever, it 
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PPM Lever", meta = (AllowPrivateAccess = "true"))
	AActor* TargetActor = nullptr;

	// None is Example For | Using 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PPM Lever", meta = (AllowPrivateAccess = "true", Bitmask))
	EPPMInteractType AcceptingInteract =
		EPPMInteractType::Simple |
		EPPMInteractType::None;

	FORCEINLINE bool bIsAnimationValid() const;

	UFUNCTION()
	// For Delegate Binding
	void OnLeverAnimationFinished();

	// Bool Variable for clarify
	bool bIsEnable = false;

protected:
	// Interact Implementation, Compare InteractType and AccpetingInteract
	virtual void OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType) override;

public:
	// API for finding out enable
	FORCEINLINE bool bIsEnabledNow() const;
};
