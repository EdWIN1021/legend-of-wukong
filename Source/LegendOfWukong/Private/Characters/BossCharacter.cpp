// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BossCharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WukongCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"


ABossCharacter::ABossCharacter() 
{
}

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

void ABossCharacter::HandleDeath()
{
	float Duration  = PlayAnimMontage(DeathAnim);
	Controller->GetBrainComponent()->StopLogic("defeated");
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABossCharacter::FinishDeathAnim, Duration, false);
	AWukongCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWukongCharacter>();
	Player->AutoEndLock(this);
}

void ABossCharacter::HandlePlayerDeath(bool bIsDead)
{
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"), EEnemyState::GameOver
	);
}

void ABossCharacter::FinishDeathAnim()
{
	Destroy();
}
