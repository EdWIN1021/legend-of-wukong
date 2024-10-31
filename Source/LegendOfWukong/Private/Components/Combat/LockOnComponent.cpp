#include "Components/Combat/LockOnComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ULockOnComponent::ULockOnComponent()
	: TargetEnemy(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComponent = Owner->GetCharacterMovement();
	SpringArm = Owner->FindComponentByClass<USpringArmComponent>();
}


void ULockOnComponent::StartLockOn()
{
	if (!Owner.IsValid() || !Controller.IsValid() || !MovementComponent.IsValid() || !SpringArm.IsValid())
	{
		return;
	}

	FHitResult Result;
	FVector Location = Owner->GetActorLocation();
	FCollisionShape Shape = FCollisionShape::MakeSphere(LockOnRadius);

	FCollisionQueryParams QueryParams(FName(TEXT("Ignore Collision Params")), false, Owner.Get());

	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		Result,
		Location,
		Location,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Shape,
		QueryParams
	);

	if (!bHasFoundTarget)
	{
		return;
	}
	
	TargetEnemy = Cast<AEnemyCharacter>(Result.GetActor());

	Controller->SetIgnoreLookInput(true);
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseControllerDesiredRotation = true;

	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 100.0f);
	TargetEnemy->ShowLockOnUI();
	OnUpdatedTargetDelegate.Broadcast(TargetEnemy.Get());
}

void ULockOnComponent::EndLockOn()
{
	TargetEnemy->HideLockOnUI();
	TargetEnemy = nullptr;
	
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bUseControllerDesiredRotation = false;
	
	SpringArm->TargetOffset = FVector::ZeroVector;
	Controller->ResetIgnoreLookInput();
	
	OnUpdatedTargetDelegate.Broadcast(TargetEnemy.Get());
}

void ULockOnComponent::ToggleLockOn()
{
	TargetEnemy.IsValid() ? EndLockOn() : StartLockOn();
}

void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TargetEnemy.IsValid() || !Owner.IsValid() || !Controller.IsValid())
	{
		return;
	}

	FVector Location = Owner->GetActorLocation();
	FVector TargetLocation = TargetEnemy->GetActorLocation();

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
