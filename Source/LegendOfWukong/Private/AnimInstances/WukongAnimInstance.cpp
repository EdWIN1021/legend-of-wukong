// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WukongAnimInstance.h"

#include "KismetAnimationLibrary.h"

void UWukongAnimInstance::UpdateVelocity()
{
	APawn* OwnerPawn  = TryGetPawnOwner();
	if(!IsValid(OwnerPawn))
	{
		return;
	}
	FVector Velocity = OwnerPawn->GetVelocity();
	
	Speed = static_cast<float>(Velocity.Length());
}

void UWukongAnimInstance::UpdatedTarget(AActor* NewTarget)
{
	bIsInCombat = IsValid(NewTarget);
}

void UWukongAnimInstance::UpdateDirection()
{
	APawn* PawnRef = TryGetPawnOwner();
	if(!IsValid(PawnRef) || !bIsInCombat) return;
	
	CurrentDirection =  UKismetAnimationLibrary::CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}

void UWukongAnimInstance::UpdateShouldPlayRelaxAnim(float DeltaSeconds, float WaitTime)
{
	if (Speed == 0)
	{
		IdleTimeout += DeltaSeconds;
	}
	else
	{
		IdleTimeout = 0; 
	}

	bShouldPlayRelaxAnim = IdleTimeout >= WaitTime;
}
