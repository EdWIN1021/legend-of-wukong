// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BossCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossCharacter::ABossCharacter()
{
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	BlackboardComp = GetController<AAIController>()->GetBlackboardComponent();

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);
}

// move to enemy
void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")));
	
	if(DetectedPawn != PawnToDetect || CurrentState != EEnemyState::Idle)
	{
		return;
	}
	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		EEnemyState::Range
	);
}
