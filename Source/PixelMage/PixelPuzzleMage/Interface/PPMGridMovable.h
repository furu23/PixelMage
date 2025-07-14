// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PPMGridMovable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPPMGridMovable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PIXELMAGE_API IPPMGridMovable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:

	// Requesting Move, after progressing movement complete launching this Function
	// Collision Check and Movement may be integrated here. in that case, define Helper Function CheckCollision()
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Movable")
	void RequestMove(const FVector2D& Direction);

	// Returning Bool type value, if Movable Object moving now.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Movable")
	bool IsCurrentlyMove() const;

	// Getter Function for Movable Object
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Movable")
	FIntPoint GetCurrentGridPosition() const;
};
