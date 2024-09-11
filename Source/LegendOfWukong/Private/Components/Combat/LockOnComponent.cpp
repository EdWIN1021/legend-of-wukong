// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/LockOnComponent.h"

ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULockOnComponent::StartLockOn()
{
	FHitResult Result;
	FVector Location = GetOwner()->GetActorLocation();
	FCollisionShape Shape  = FCollisionShape::MakeSphere((750.f));
	
	FCollisionQueryParams IgnoreParams = FCollisionQueryParams(
		FName(TEXT("Ignore Collision Params")),
		false,
		GetOwner()
	);
	
	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		Result,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Shape,
		IgnoreParams
		);
	if(!bHasFoundTarget)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Actor Detected: %s"), *Result.GetActor()->GetName());
}

void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

