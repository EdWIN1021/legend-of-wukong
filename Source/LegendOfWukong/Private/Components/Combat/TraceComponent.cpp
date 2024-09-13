// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"

#include "SWarningOrErrorBox.h"
#include "Characters/BaseCharacter.h"
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
	
	TArray<FHitResult> AllResults;

	for(const FTraceSockets Socket : Sockets)
	{
		FVector StartSocketLocation = SkeletakMesh->GetSocketLocation(Socket.Start);
		FVector EndSocketLocation = SkeletakMesh->GetSocketLocation(Socket.End);
		FQuat ShapeRotation = SkeletakMesh->GetSocketQuaternion(Socket.Rotation);

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

		for(FHitResult Hit : Results)
		{
			AllResults.Add(Hit);
		}

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
	
	if(AllResults.Num() == 0)
	{
		return;
	}
	
	float CharacterDamage = 0.0f;

	
	if(ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner()))
	{	
		CharacterDamage = Owner->ApplyDamage();
	}

	UE_LOG(LogTemp, Warning, TEXT("The value of MyFloat is: %f"), CharacterDamage);
	
	FDamageEvent TargetAttackedEvent; 
	
	for(const FHitResult& Hit : AllResults)
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

