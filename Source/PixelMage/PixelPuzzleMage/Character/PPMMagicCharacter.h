// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PPMPlayer.h"
#include "../Data/PPMDataType.h"

#include "PaperFlipbookComponent.h"

#include "PPMMagicCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PIXELMAGE_API APPMMagicCharacter final : public APPMPlayer
{
	GENERATED_BODY()

public:
	APPMMagicCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float Deltatime) override;

private:
	// Component and Flipbook Here
	// Flipbook array
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magic Character", meta = (AllowPrivateAccess = "true"))
	TMap<EPPMCharacterState, class UPaperFlipbook*> FlipbookMap;

	// for ability check
	TSet<EMagicAbility> AbilityCurrent;

	// Ability Function. don't Implement now, BlueprintNativeEvent reflection declared
	virtual void UseAbility(int32 Abilities) override;

public:
	// Change Flipbook Animation
	UFUNCTION(BlueprintCallable, Category = "Magic Character")
	void UpdateAnimation(EPPMCharacterState Action);
};
