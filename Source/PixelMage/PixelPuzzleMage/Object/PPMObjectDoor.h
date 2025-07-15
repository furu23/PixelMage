// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Data/PPMDataType.h"
#include "../Interface/PPMInteractable.h"

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PPMObjectDoor.generated.h"

UCLASS()
class PIXELMAGE_API APPMObjectDoor : public AActor, public IPPMInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPMObjectDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "PPM Door", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* DoorAnimation = nullptr;

	// Accepting Type of Interact 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PPM Door", meta = (AllowPrivateAccess = "true", Bitmask))
	EPPMInteractType AcceptingInteract = EPPMInteractType::Lever;

	FORCEINLINE bool bIsAnimationValid() const;

	UFUNCTION()
	// For Delegate Binding
	void OnDoorAnimationFinished();

	// Bool Variable for clarify
	bool bIsEnable = false;

protected:
	// Interact Implementation, Compare InteractType and AccpetingInteract
	virtual void OnInteract_Implementation(AActor* Interactor, EPPMInteractType InteractType) override;

public:
	// API for finding out enable
	FORCEINLINE bool bIsEnabledNow() const;
};
