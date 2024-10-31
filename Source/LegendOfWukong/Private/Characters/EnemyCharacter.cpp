// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/EnemyCharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Characters/WukongCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/LockOnComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::HandleDeath()
{
	float AnimDuration  = PlayAnimMontage(DeathAnim);
	
	GetController<AAIController>()->GetBrainComponent()->StopLogic("defeated");
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::FinishDeathAnim, AnimDuration, false);
	EndLockOn();
}

void AEnemyCharacter::FinishDeathAnim()
{
	Destroy();
}

void AEnemyCharacter::EndLockOn()
{
	AWukongCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWukongCharacter>();
	ULockOnComponent* LockOnComp = Player->GetLockOnComponent();
	if(LockOnComp->TargetEnemy == this){
		LockOnComp->EndLockOn();
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
