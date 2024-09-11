// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef = GetOwner<ACharacter>();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::ComboAttack()
{
	if(!bCanAttack)
	{
		return;
	}
	
	bCanAttack = false;
	
	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);
	ComboCounter++;

	int MaxCombo = AttackAnimations.Num();
	ComboCounter = UKismetMathLibrary::Wrap(ComboCounter, -1, MaxCombo - 1);
}

void UCombatComponent::HandleRestAttack()
{
	bCanAttack = true;
}

