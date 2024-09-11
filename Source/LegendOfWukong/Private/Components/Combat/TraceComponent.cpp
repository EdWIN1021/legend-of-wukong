// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletakMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector StartSocketLocation = SkeletakMesh->GetSocketLocation(Start);
	FVector EndSocketLocation = SkeletakMesh->GetSocketLocation(End);
	FQuat ShapeRotation = SkeletakMesh->GetSocketQuaternion(Rotation);



	TArray<FHitResult> Results;
	double WeaponDistance = FVector::Distance(StartSocketLocation, EndSocketLocation);
	FVector BoxHalfExtent(BoxCollisionLength, BoxCollisionLength, WeaponDistance);;
	BoxHalfExtent /= 2;

	FCollisionShape Box = FCollisionShape::MakeBox(BoxHalfExtent);
	FCollisionQueryParams QueryParams(FName(TEXT("Ignore Collision Params")), false, GetOwner());
	
	bool bHasFoundTarget = GetWorld()->SweepMultiByChannel(
		Results,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECC_GameTraceChannel1,
		Box,
		QueryParams
		);

	if(bDebugMode)
	{
		FVector CenterPoint = UKismetMathLibrary::VLerp(StartSocketLocation, EndSocketLocation, 0.5f);
		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			bHasFoundTarget ? FLinearColor::Green : FLinearColor::Red,
			ShapeRotation.Rotator(),
			1.0f,
			2.0f
			);
	}
}

