// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BossCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"


ABossCharacter::ABossCharacter()
{
	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComp"));
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

float ABossCharacter::GetPercentage(EAttribute Current, EAttribute Max)
{
	return StatsComp->Attributes[Current] / StatsComp->Attributes[Max];
}

float ABossCharacter::ApplyDamage()
{
	return StatsComp->Attributes[EAttribute::Strength];
}

void ABossCharacter::ReduceHealth(float Amount)
{
	if(StatsComp->Attributes[EAttribute::Health] <= 0)
	{
		return;
	}
    	
	StatsComp->Attributes[EAttribute::Health] -= Amount;
	StatsComp->Attributes[EAttribute::Health] = UKismetMathLibrary::FClamp(StatsComp->Attributes[EAttribute::Health], 0,StatsComp->Attributes[EAttribute::MaxHealth]);

	StatsComp->OnUpdateHealthUIDelegate.Broadcast(
	GetPercentage(EAttribute::Health, EAttribute::MaxHealth));

}
