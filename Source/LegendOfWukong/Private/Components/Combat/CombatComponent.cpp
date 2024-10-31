// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"
#include "Characters/WukongCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef = GetOwner<ABaseCharacter>();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::ComboAttack()
{
	AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(CharacterRef);
	// if(WukongCharacter && !WukongCharacter->HasEnoughStamina(StaminaCost))
	// {
	// 	return;
	// }

	if(!bCanAttack)
	{
		return;
	}
	
	bCanAttack = false;
	Cast<UWukongAnimInstance>(WukongCharacter->GetMesh()->GetAnimInstance())->IdleTimeout = 0;
	
	
	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);
	ComboCounter++;

	int MaxCombo = AttackAnimations.Num();
	ComboCounter = UKismetMathLibrary::Wrap(ComboCounter, -1, MaxCombo - 1);
	// WukongCharacter->ReduceStamina(StaminaCost);
}

void UCombatComponent::HandleResetAttack()
{
	bCanAttack = true;
}

