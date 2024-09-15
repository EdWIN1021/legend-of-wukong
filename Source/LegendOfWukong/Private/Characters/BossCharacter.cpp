// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BossCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WukongCharacter.h"
#include "Components/StatsComponent.h"

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	Controller = GetController<AAIController>();
	BlackboardComp = GetController<AAIController>()->GetBlackboardComponent();
	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);

	GetWorld()->GetFirstPlayerController()->GetPawn<AWukongCharacter>()->StatsComp->OnZeroHealthDelegate.AddDynamic(
		this, &ABossCharacter::HandlePlayerDeath
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


