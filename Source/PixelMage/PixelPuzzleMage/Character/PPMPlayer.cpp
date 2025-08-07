#include "PPMPlayer.h"

#include "Engine/Engine.h" // 수정
#include "Engine/CollisionProfile.h"


APPMPlayer::APPMPlayer()
{
	// Make Components
	GridSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("GridSpringArmComponent");
	GridSpringArmComponent->SetupAttachment(RootComponent);

	GridCameraComp = CreateDefaultSubobject<UCameraComponent>("GridCameraComp");
	GridCameraComp->SetupAttachment(GridSpringArmComponent);

	// Camera Height, Helper Function Will change this value
	GridSpringArmComponent->TargetArmLength = 200.0f;
	// Camera Rotation
	GridSpringArmComponent->SetRelativeRotation(FRotator(0, 10.0f, -90.0f));

	// disable Character influence Camera
	GridSpringArmComponent->bInheritPitch = false;
	GridSpringArmComponent->bInheritRoll = false;
	GridSpringArmComponent->bInheritYaw = false;

	// Make Interact Comp
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetBoxExtent(FVector(GRID_TILE_SIZE / 2, GRID_TILE_SIZE / 2, GRID_TILE_SIZE / 2));
	TriggerVolume->SetRelativeLocation(FVector(GRID_TILE_SIZE, 0, 0));

	// Confirmation of Debug
	TriggerVolume->SetGenerateOverlapEvents(true);

	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionObjectType(ECC_Pawn);
	TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);


	// Interact Box Implementation Here
}

void APPMPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* GridPlayerController = Cast<APlayerController>(GetController());

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APPMPlayer::OnInteractOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APPMPlayer::OnInteractOverlapEnd);

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
	if (ensure(GridEnhancedInputComponent))
	{
		// Bind function for GridMove
		GridEnhancedInputComponent->BindAction(GridIAMove, ETriggerEvent::Triggered, this, &APPMPlayer::GridMove);
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
	UE_LOG(LogTemp, Warning, TEXT("OverlapStart, %s, %s, %s"), *OverlappedComp->GetFName().ToString(), *OtherActor->GetFName().ToString(), *OtherComp->GetFName().ToString());
}

void APPMPlayer::OnInteractOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ensure(Cast<IPPMInteractable>(OtherActor) == Interactable))
		Interactable = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("OverlapEnd, %s, %s, %s"), *OverlappedComp->GetFName().ToString(), *OtherActor->GetFName().ToString(), *OtherComp->GetFName().ToString());
}

void APPMPlayer::InteractWithTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractWithTarget Called. Now Interactable : %p"), Interactable);

	if (ensure(Interactable))
		Interactable->Execute_OnInteract(Cast<UObject>(Interactable), Cast<AActor>(this), EPPMInteractType::Simple);
	// Implementation Here
}

void APPMPlayer::GridMove(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("1. GridMove Called!")); // <-- 수정

	// get Direction of Movement Input;
	FVector TempVector = InputValue.Get<FVector>();
	FVector2D InputDirection(TempVector.X, TempVector.Z);

	// Delegate Broadcast Here

	IPPMGridMovable::Execute_RequestMove(this, InputDirection);
	const FVector2D NormalizedDirection = InputDirection.GetSafeNormal();
	const FVector Direction3D = FVector(NormalizedDirection.X, 0.0f, NormalizedDirection.Y);
	TriggerVolume->SetRelativeRotation(TempVector.Rotation());
	TriggerVolume->SetRelativeLocation(TempVector * GRID_TILE_SIZE);
}

FORCEINLINE void APPMPlayer::SetCameraHeight(float CameraHeight)
{
	GridSpringArmComponent->TargetArmLength = CameraHeight;
}

