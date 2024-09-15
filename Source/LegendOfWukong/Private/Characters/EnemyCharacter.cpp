// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/EnemyCharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Characters/WukongCharacter.h"
#include "Components/CapsuleComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::HandleDeath()
{
	float Duration  = PlayAnimMontage(DeathAnim);
	
	GetController<AAIController>()->GetBrainComponent()->StopLogic("defeated");
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AEnemyCharacter::FinishDeathAnim, Duration, false);
	AWukongCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWukongCharacter>();
	Player->AutoEndLock(this);
}

void AEnemyCharacter::FinishDeathAnim()
{
	Destroy();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
