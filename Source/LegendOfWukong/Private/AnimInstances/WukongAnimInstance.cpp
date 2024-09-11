// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WukongAnimInstance.h"

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
