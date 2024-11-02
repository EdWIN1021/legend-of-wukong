// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BossCharacter.h"
#include "AIController.h"
#include "AbilitySystem/WukongAbilitySystemComponent.h"
#include "AttributeSets/WukongAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WukongCharacter.h"



void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent"));
	}

	if (AttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeSet"));
	}

	Controller = GetController<AAIController>();
	BlackboardComp = GetController<AAIController>()->GetBlackboardComponent();
	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);
}

void ABossCharacter::RandomAttack()
{
	int RandomIndex = FMath::RandRange(0, AttackAnimations.Num() - 1);
	AnimDuration = GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimations[RandomIndex]);
}

float ABossCharacter::GetAnimDuration()
{
	return AnimDuration;
}


void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")));
	
	if(DetectedPawn != PawnToDetect || CurrentState != EEnemyState::Idle)
	{
		return;
	}

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"), 
		EEnemyState::Charge
	);
}

void ABossCharacter::HandlePlayerDeath(bool bIsDead)
{
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"), EEnemyState::GameOver
	);
}


