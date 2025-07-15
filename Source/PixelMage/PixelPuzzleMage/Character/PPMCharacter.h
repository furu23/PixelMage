// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Interface/PPMGridMovable.h"
#include "../Data/PPMDataType.h"

#include "PaperCharacter.h"

#include "PPMCharacter.generated.h"



/**
 * 
 */
UCLASS()
class PIXELMAGE_API APPMCharacter : public APaperCharacter, public IPPMGridMovable
{
	GENERATED_BODY()

public:
	APPMCharacter();

protected:
	// Begin Play
	virtual void BeginPlay() override;

	// Tick
	virtual void Tick(float DeltaTime) override;

private:
	// GridStat Struct, decline to private member for encapsulation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Character", meta = (AllowPrivateAccess = "true"))
	FPPMCharacterStats CharacterStats;

	// For Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Character", meta = (AllowPrivateAccess = "true"))
	FIntPoint TargetLocation;

	// Movement Check Variable
	bool bIsMoving = false;

protected:
	UFUNCTION(BlueprintCallable, Category = "Grid Character")
	// Not implement Detail in GridCharacter
	virtual void UseAbility(int32 Abilities);

public:
	// Movement Implementation
	virtual void RequestMove_Implementation(const FVector2D& Direction) override;

	// Kind of bool Function
	virtual bool IsCurrentlyMove_Implementation() const override;

	// Kind of GetLocation
	virtual FIntPoint GetCurrentGridPosition_Implementation() const override;

	// Situation for get damaged, last priority implementation
	// invincible time and spotting red Damaging effects
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Grid Character")
	void OnTakeDamage(int32 Damage);

	// RequestMove Helper Function
	bool CanMoveTo(const FIntPoint& TargetPosition);

	// TileSize is Constance, UPROPERTY doesn't needed
	const float GRID_TILE_SIZE = 16.0f;
};
