// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Data/PPMDataType.h"
#include "PPMBaseInteracter.h"

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PPMObjectDoor.generated.h"

UCLASS()
class PIXELMAGE_API APPMObjectDoor : public APPMBaseInteracter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPMObjectDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	// For Delegate Binding
	void OnDoorAnimationFinished();
};
