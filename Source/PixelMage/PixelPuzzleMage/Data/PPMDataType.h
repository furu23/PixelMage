#pragma once

#include "CoreMinimal.h"

#include "PPMDataType.generated.h"

USTRUCT(BlueprintType)
struct FPPMCharacterStats
{
	GENERATED_BODY()

public:
	// Current Position of Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Character")
	FIntPoint CharacterPosition;

	// Current HP of Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Character")
	int32 HP;

	// Character Movement Speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Character")
	float MovementSpeed = 10.0f;
};


// Ability Names Here
UENUM(BlueprintType)
enum class EMagicAbility : uint8
{
	Ability1,
	Ability2,
	Ability3,
	Ability4
};

// Flipbook Animations Here
UENUM(BlueprintType)
enum class EPPMCharacterState : uint8
{
	Idle,
	Walking,
	Attack,
	Interact
};