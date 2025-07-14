// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Data/PPMDataType.h"
#include "../Component/PPMStateComponent.h"

#include "Components/ActorComponent.h"

#include "PPMAbilityBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIXELMAGE_API UPPMAbilityBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPMAbilityBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Ability Base")
	float Cooldown = 10.0f;

	UPROPERTY(EditInstanceOnly, Category = "Ability Base")
	EPPMCharacterState AssignedState = EPPMCharacterState::Idle;

	// Use Super:: to inherited Class
	virtual bool Activate(AActor* instigator);

	// Use Super:: to inherited Class
	virtual bool CanActivate(AActor* instigator) const;
};
