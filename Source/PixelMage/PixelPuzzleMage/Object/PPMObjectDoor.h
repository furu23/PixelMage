// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Data/PPMDataType.h"
#include "../Interface/PPMInteractable.h"

#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
