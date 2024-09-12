// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"
#include "Components/ActionsComponent.h"
#include "Components/Combat/BlockComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "Components/Combat/TraceComponent.h"

AWukongCharacter::AWukongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LockonComp = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockonComp"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComp"));
	BlockComp = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComp"));
	ActionsComp = CreateDefaultSubobject<UActionsComponent>(TEXT("ActionsComp"));
}

float AWukongCharacter::ApplyDamage()
{
	Super::ApplyDamage();
	return Attributes[EAttribute::Strength];
}

void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();
	WukongAnim = Cast<UWukongAnimInstance>(GetMesh()->GetAnimInstance());
}
