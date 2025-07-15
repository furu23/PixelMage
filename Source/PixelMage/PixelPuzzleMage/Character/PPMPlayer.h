#pragma once

#include "CoreMinimal.h"

#include "PPMCharacter.h"
#include "../Data/PPMDataType.h"
#include "../Interface/PPMInteractable.h"

#include "Delegates/DelegateCombinations.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


#include "PPMPlayer.generated.h"




UCLASS()
class PIXELMAGE_API APPMPlayer : public APPMCharacter
{
	GENERATED_BODY()

public:
	APPMPlayer();

	// No Public API Function.
	// if You want more Abstract Character, Please inherit and specify this Class

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float Deltatime) override;

	// Binding Inputs to Function
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Camera object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Player", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* GridCameraComp;

	// default IMC variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GridIMCDefault = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* GridIAMove = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IAInteract = nullptr;

  // declare overlap begin function
	UFUNCTION()
	void OnInteractOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnInteractOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IPPMInteractable* Interactable = nullptr;

protected:
	// TrigerVolume, for interact
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Player", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerVolume;

	// SpringArm for Top-Down pixel art Game
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Player", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* GridSpringArmComponent;

	// check Interface Implementation of Activate Function on Object, Also don't Implement now
	// lever, box, key
	UFUNCTION(BlueprintCallable, Category = "Grid Player")
	void InteractWithTarget();

	// Move Function
	UFUNCTION(BlueprintCallable, Category = "Grid Player")
	void GridMove(const FInputActionValue& InputValue);

public:
	// Camera Height Helper Function
	UFUNCTION(BlueprintCallable, Category = "Grid Player")
	FORCEINLINE void SetCameraHeight(float CameraHeight);
};