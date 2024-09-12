// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"

#include "SWarningOrErrorBox.h"
#include "Engine/DamageEvents.h"
#include "Interfaces/Fighter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletakMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsAttacking)
	{
		return;
	}
	
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

	if(Results.Num() == 0)
	{
		return;
	}

	float CharacterDamage = 0.0f;
	IFighter* FighterRef = Cast<IFighter>(GetOwner());

	if(FighterRef)
	{
		CharacterDamage = FighterRef->GetDamage();
	}

	FDamageEvent TargetAttackedEvent; 
	
	for(const FHitResult& Hit : Results)
	{
		AActor* Target = Hit.GetActor();

		if(TargetsToIgnore.Contains(Target))
		{
			continue;
		}
		Target->TakeDamage(
			CharacterDamage,
			TargetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner());

		TargetsToIgnore.AddUnique(Target);
	}
}

