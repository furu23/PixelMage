#include "PPMPlayer.h"

#include "Engine/Engine.h" // 수정


APPMPlayer::APPMPlayer()
{
	// Make Components
	GridSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("GridSpringArmComponent");
	GridSpringArmComponent->SetupAttachment(RootComponent);

	GridCameraComp = CreateDefaultSubobject<UCameraComponent>("GridCameraComp");
	GridCameraComp->SetupAttachment(GridSpringArmComponent);

	// Camera Height, Helper Function Will change this value
	GridSpringArmComponent->TargetArmLength = 100.0f;
	// Camera Rotation
	GridSpringArmComponent->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	// disable Character influence Camera
	GridSpringArmComponent->bInheritPitch = false;
	GridSpringArmComponent->bInheritRoll = false;
	GridSpringArmComponent->bInheritYaw = false;

	// Make Interact Comp
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	TriggerVolume->SetupAttachment(RootComponent);

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APPMPlayer::OnInteractOverlapBegin);

	// Interact Box Implementation Here
}

void APPMPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* GridPlayerController = Cast<APlayerController>(GetController());

	if (ensure(GridPlayerController != nullptr))
	{
		UEnhancedInputLocalPlayerSubsystem* GridInputSubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GridPlayerController->GetLocalPlayer());

		if (ensure(GridInputSubSystem != nullptr))
		{
			// IMC 에셋이 할당되었는지도 확인
			if (ensure(GridIMCDefault != nullptr))
			{
				GridInputSubSystem->AddMappingContext(GridIMCDefault, 0);
				UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context ADDED SUCCESSFULLY."));
			}
		}
	}
}
	// Success for Casting
	//if (GridPlayerController)
	//{
	//	UEnhancedInputLocalPlayerSubsystem* GridInputSubSystem = 
	//		GridPlayerController
	//		->GetLocalPlayer()
	//		->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	//	if (GridInputSubSystem)
	//	{
	//		GridInputSubSystem->AddMappingContext(GridIMCDefault, 0);
	//	}
	//	else
	//	{
	//		// later, Error care here
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("GridPlayer::BeginPlay() => Casting or nullptr Error"));
	//	// care code here
	//}
	//}

void APPMPlayer::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void APPMPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Casting for UEnhancedInputComponent
	UEnhancedInputComponent* GridEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (GridEnhancedInputComponent)
	{
		// Bind function for GridMove
		GridEnhancedInputComponent->BindAction(GridIAMove, ETriggerEvent::Ongoing, this, &APPMPlayer::GridMove);
		GridEnhancedInputComponent->BindAction(IAInteract, ETriggerEvent::Started, this, &APPMPlayer::InteractWithTarget);
		// Another Actions are Here
	}
}

void APPMPlayer::OnInteractOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPPMInteractable* Target = Cast<IPPMInteractable>(OtherActor);
	if (Target)
	{
		// Component Box here
		Interactable = Target;
	}
}

void APPMPlayer::OnInteractOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<IPPMInteractable>(OtherActor) == Interactable)
		Interactable = nullptr;
}

void APPMPlayer::InteractWithTarget()
{
	if (Interactable)
		Interactable->OnInteract();
	// Implementation Here
}

// use FORCEINLINE TRADEOFF?	
void APPMPlayer::GridMove(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("1. GridMove Called!")); // <-- 수정

	// get Direction of Movement Input;
	FVector2D InputDirection = InputValue.Get<FVector2D>();

	// Delegate Broadcast Here

	IPPMGridMovable::Execute_RequestMove(this, InputDirection);
}

FORCEINLINE void APPMPlayer::SetCameraHeight(float CameraHeight)
{
	GridSpringArmComponent->TargetArmLength = CameraHeight;
}

