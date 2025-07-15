// Fill out your copyright notice in the Description page of Project Settings.


#include "PPMCharacter.h"


APPMCharacter::APPMCharacter()
{
	CharacterStats.HP = 10;
}

void APPMCharacter::BeginPlay()
{
	Super::BeginPlay();

	FVector CurrentWorldLocation = GetActorLocation();
	CharacterStats.CharacterPosition.X = FMath::RoundToInt(CurrentWorldLocation.X / GRID_TILE_SIZE);
	CharacterStats.CharacterPosition.Y = FMath::RoundToInt(CurrentWorldLocation.Y / GRID_TILE_SIZE);

	// Snap to Logical Location for Error caring (Grid Location)
	FVector SnappedWorldLocation(
		CharacterStats.CharacterPosition.X * GRID_TILE_SIZE,
		CharacterStats.CharacterPosition.Y * GRID_TILE_SIZE,
		CurrentWorldLocation.Z
	);
	SetActorLocation(SnappedWorldLocation);
	TargetLocation = CharacterStats.CharacterPosition;
}

void APPMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsMoving) return;

	// Decline Datas For VInterP
	FVector CurrentWorldLocation = this->GetActorLocation();
	// Refactoring here After
	FVector TargetWorldLocation(TargetLocation.X * GRID_TILE_SIZE, TargetLocation.Y * GRID_TILE_SIZE, CurrentWorldLocation.Z);

	// if CurrentWorldLocation and TargetWorldLocation is enough to near, Set Axis to TargetWorldLoaction
	if (FMath::Abs<double>(FVector::DistXY(CurrentWorldLocation, TargetWorldLocation)) <= 0.5)
	{
		this->SetActorLocation(TargetWorldLocation);
		CharacterStats.CharacterPosition = TargetLocation;
		bIsMoving = false;
		return;
	}

	// Start to Move
	FVector NewWorldLocation = FMath::VInterpTo(
		CurrentWorldLocation,
		TargetWorldLocation,
		DeltaTime,
		CharacterStats.MovementSpeed
	);

	this->SetActorLocation(NewWorldLocation);
}

void APPMCharacter::RequestMove_Implementation(const FVector2D& Direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("2. RequestMove Called!")); // <-- 수정

	// --- 디버깅 코드 시작 ---
	FString IsMovingStatus = FString::Printf(TEXT("3. bIsMoving = %s"),
		IsCurrentlyMove_Implementation() ? TEXT("true") : TEXT("false"));
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, IsMovingStatus);
	// --- 디버깅 코드 끝 ---

	if (ensure(IsCurrentlyMove_Implementation()))
	{
		return;
	}

	TargetLocation = GetCurrentGridPosition_Implementation() + Direction.IntPoint();
	if (CanMoveTo(TargetLocation))
	{
		bIsMoving = true;
	}
	else
		TargetLocation = CharacterStats.CharacterPosition;
}

FORCEINLINE bool APPMCharacter::IsCurrentlyMove_Implementation() const
{
	return bIsMoving;
}

FORCEINLINE FIntPoint APPMCharacter::GetCurrentGridPosition_Implementation() const
{
	return CharacterStats.CharacterPosition;
}

void APPMCharacter::UseAbility(int32 Abilities)
{
	// basic implementation here, Detailed Implementation Must be in Final Class
}

bool APPMCharacter::CanMoveTo(const FIntPoint& TargetPosition)
{
	// (!!!) After Implementation Level, Scan to TargetPosition is in Valid axis
	FVector Start = this->GetActorLocation();
	// Target Position and  Convert it to World Location
	FVector End(TargetPosition.X * GRID_TILE_SIZE, TargetPosition.Y * GRID_TILE_SIZE, Start.Z);

	// Collision Params, After Map Implementation Check Sprites here
	FCollisionQueryParams GridParams;
	GridParams.AddIgnoredActor(this);

	FVector HalfSize = FVector::One() * GRID_TILE_SIZE / 2;

	FHitResult GridHitResult;
	GetWorld()->SweepSingleByChannel(
		GridHitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_WorldStatic,
		FCollisionShape::MakeBox(HalfSize),
		GridParams
	);

	FColor DebugColor = GridHitResult.IsValidBlockingHit() ? FColor::Red : FColor::Green;
	DrawDebugBox(GetWorld(), End, HalfSize, DebugColor, false, 2.0f, 0, 1.0f);

	return !GridHitResult.IsValidBlockingHit();
}
