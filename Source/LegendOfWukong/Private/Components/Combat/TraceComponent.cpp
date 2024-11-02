// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributeSets/WukongAttributeSet.h"
#include "Characters/BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "WukongGameplayTags/WukongGameplayTags.h"

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
	WeaponMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
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
		FVector StartSocketLocation = WeaponMesh->GetSocketLocation(Socket.Start);
		FVector EndSocketLocation = WeaponMesh->GetSocketLocation(Socket.End);
		FQuat ShapeRotation = WeaponMesh->GetSocketQuaternion(Socket.Rotation);

		TArray<FHitResult> Results;
		double WeaponDistance = FVector::Distance(StartSocketLocation, EndSocketLocation);
		FVector BoxHalfExtent(BoxCollisionLength, BoxCollisionLength, WeaponDistance);
		BoxHalfExtent /= 2;

		FCollisionShape Box = FCollisionShape::MakeBox(BoxHalfExtent);
		FCollisionQueryParams QueryParams(FName(TEXT("Ignore Collision Params")), false, GetOwner());
	
		GetWorld()->SweepMultiByChannel(
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
	}
	
	if(AllResults.Num() == 0) return;

	UAbilitySystemComponent* SourceASC = Cast<ABaseCharacter>(GetOwner())->GetAbilitySystemComponent();
	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1, SourceASC->MakeEffectContext());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, WukongGameplayTags::Damage, GetOwnerDamage(GetOwner()));

	float Damage = GetOwnerDamage(GetOwner());

	for(const FHitResult& Hit : AllResults)
	{
		FDamageEvent TargetAttackedEvent;
		AActor* Target = Hit.GetActor();

		if(TargetsToIgnore.Contains(Target)) continue;

		if(UAbilitySystemComponent* TargetASC = Cast<ABaseCharacter>(Target)->GetAbilitySystemComponent())
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		};
		TargetsToIgnore.AddUnique(Target);
	}
}

float UTraceComponent::GetOwnerDamage(AActor* InOwner){
	if(ABaseCharacter* Owner = Cast<ABaseCharacter>(InOwner))
	{	
		UWukongAttributeSet* AS = Cast<UWukongAttributeSet>(Owner->GetAttributeSet());
		return  AS->GetStrength();
	}
	return 0.f;
}

