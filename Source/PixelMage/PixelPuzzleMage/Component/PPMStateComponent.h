// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Data/PPMDataType.h"

#include "Components/ActorComponent.h"

#include "PPMStateComponent.generated.h"

// Struct For Managing AllowStateSet
USTRUCT(BlueprintType)
struct FPPMStateTransition
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State Component", meta = (AllowPrivateAccess = "true"))
	TSet<EPPMCharacterState> ValidTransitionSet;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIXELMAGE_API UPPMStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPMStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Current State Now
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State Component", meta = (AllowPrivateAccess = "true"))
	EPPMCharacterState CurrentState;

	// State Set that can be change to next
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State Component", meta = (AllowPrivateAccess = "true", ToolTip = "캐릭터의 상태 규칙을 정의합니다."))
	TMap<EPPMCharacterState, FPPMStateTransition> AllowState;

public:
	// Delegate
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanged, EPPMCharacterState, StateArgument);


	
	UPROPERTY(BlueprintAssignable)
	FOnCharacterStateChanged OnChangeState;

	void foo()
	{

	}


	UFUNCTION(BlueprintCallable)
	void SetState(EPPMCharacterState NewState);

	UFUNCTION(BlueprintPure)
	FORCEINLINE EPPMCharacterState GetCurrentState() const;

	UFUNCTION(BlueprintCallable)
	void SetNewAllowState(EPPMCharacterState TargetState, EPPMCharacterState NewAllowState);

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsInAllowState(EPPMCharacterState QueryState);
};
