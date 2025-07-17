// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PPMBaseInteracter.h"
#include "../Data/PPMDataType.h"

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PPMObjectLever.generated.h"

UCLASS()
class PIXELMAGE_API APPMObjectLever : public APPMBaseInteracter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPMObjectLever();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	// For Delegate Binding
	void OnLeverAnimationFinished();
};
