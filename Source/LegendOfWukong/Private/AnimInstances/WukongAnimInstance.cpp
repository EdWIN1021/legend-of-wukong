// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WukongAnimInstance.h"

#include "KismetAnimationLibrary.h"

void UWukongAnimInstance::UpdateSpeed()
{
	APawn* OwnerPawn { TryGetPawnOwner() };
	if(!IsValid(OwnerPawn))
	{
		return;
	}
	FVector Velocity = OwnerPawn->GetVelocity();
	Speed = static_cast<float>(Velocity.Length());
}

void UWukongAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UWukongAnimInstance::UpdateDirection()
{
	APawn* PawnRef = TryGetPawnOwner();
	if(!IsValid(PawnRef))
	{
		return;
	}

	if(!bIsInCombat)
	{
		return;
	}
	
	CurrentDirection =  UKismetAnimationLibrary::CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}
