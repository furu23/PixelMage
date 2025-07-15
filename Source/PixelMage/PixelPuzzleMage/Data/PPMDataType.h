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

// interact Enum here
UENUM(BlueprintType, meta =(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPPMInteractType : uint8
{
	None = 0x0 UMETA(Hidden),
	Simple = (1 << 0),
	Lever = (1 << 1),
	FireMagic = (1 << 2),
	Attack = (1 << 3)
};

ENUM_CLASS_FLAGS(EPPMInteractType);