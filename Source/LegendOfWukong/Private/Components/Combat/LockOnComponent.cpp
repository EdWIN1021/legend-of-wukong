#include "Components/Combat/LockOnComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Constructor
ULockOnComponent::ULockOnComponent()
	: TargetActor(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

// BeginPlay - Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize owner and components
	OwnerPawn = GetOwner<ACharacter>();
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: OwnerPawn is not valid!"));
		return;
	}

	Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: Controller is not valid!"));
		return;
	}

	MovementComponent = OwnerPawn->GetCharacterMovement();
	if (!MovementComponent.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: MovementComponent is not valid!"));
	}

	SpringArm = OwnerPawn->FindComponentByClass<USpringArmComponent>();
	if (!SpringArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: SpringArm is not valid!"));
	}
}


void ULockOnComponent::StartLockOn(float Radius)
{
	if (!OwnerPawn || !Controller.IsValid() || !MovementComponent.IsValid() || !SpringArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: Required components are missing."));
		return;
	}

	FHitResult Result;
	FVector Location = OwnerPawn->GetActorLocation();
	FCollisionShape Shape = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams QueryParams(FName(TEXT("Ignore Collision Params")), false, OwnerPawn);

	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		Result,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Shape,
		QueryParams
	);

	if (!bHasFoundTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULockOnComponent: No target found within radius."));
		return;
	}

	TargetActor = Result.GetActor();

	Controller->SetIgnoreLookInput(true);
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseControllerDesiredRotation = true;

	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 100.0f);
}

void ULockOnComponent::EndLockOn()
{
	TargetActor = nullptr;
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bUseControllerDesiredRotation = false;
	SpringArm->TargetOffset = FVector::ZeroVector;
	Controller->ResetIgnoreLookInput();
}

void ULockOnComponent::ToggleLockOn(float Radius)
{
	if(TargetActor.IsValid())
	{
		EndLockOn();
	} else
	{
		StartLockOn(Radius);
	}
}

void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TargetActor.IsValid() || !OwnerPawn || !Controller.IsValid())
	{
		return;
	}

	FVector Location = OwnerPawn->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	double TargetDistance = FVector::Distance(Location, TargetLocation);

	if(TargetDistance >= AutoEndLockOnDistance)
	{
		EndLockOn();
		return;
	}
	
	TargetLocation.Z -= 125.0f;
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Location, TargetLocation);
	Controller->SetControlRotation(NewRotation);
}
