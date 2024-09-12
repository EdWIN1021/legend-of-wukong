// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"
#include "Components/Combat/BlockComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "Components/Combat/TraceComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AWukongCharacter::AWukongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LockonComp = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockonComp"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComp"));
	BlockComp = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComp"));
}

void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();
	WukongAnim = Cast<UWukongAnimInstance>(GetMesh()->GetAnimInstance());
}

float AWukongCharacter::ApplyDamage() // move to base ?
{
	Super::ApplyDamage();
	return Attributes[EAttribute::Strength];
}

void AWukongCharacter::ReduceStamina(float Amount)
{
	Attributes[EAttribute::Stamina] -= Amount;
	Attributes[EAttribute::Stamina] = UKismetMathLibrary::FClamp(Attributes[EAttribute::Stamina], 0,Attributes[EAttribute::MaxStamina] );
	bCanRestore = false;

	FLatentActionInfo FunctionInfo(0, 100, TEXT("EnableStore"), this);
	
	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo
	);
}

bool AWukongCharacter::HasEnoughStamina(float Cost)
{
	return Attributes[EAttribute::Stamina] >= Cost;
}

void AWukongCharacter::EnableStore()
{
	bCanRestore = true;
}

void AWukongCharacter::RestoreStamina()
{
	if(!bCanRestore)
	{
		return;	
	}
	
	Attributes[EAttribute::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Attributes[EAttribute::Stamina],
		Attributes[EAttribute::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRestoreRate
		);
	
}

void AWukongCharacter::Sprint()
{
	if(!HasEnoughStamina(SprintCost))
	{
		Walk();
		return;
	}

	if(GetCharacterMovement()->Velocity.Equals(FVector::ZeroVector, 1))
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	ReduceStamina(SprintCost);
}

void AWukongCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


