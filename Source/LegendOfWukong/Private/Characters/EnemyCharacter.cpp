// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/EnemyCharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "AbilitySystem/WukongAbilitySystemComponent.h"
#include "AttributeSets/WukongAttributeSet.h"
#include "Characters/WukongCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/LockOnComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UWukongAbilitySystemComponent>(TEXT("EnemyAbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UWukongAttributeSet>(TEXT("EnemyAttributeSet"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		BindDelegates();
		InitializeAttributes();
	}
}

void AEnemyCharacter::BindDelegates()
{
	if(const UWukongAttributeSet* AS = Cast<UWukongAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	}
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
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


