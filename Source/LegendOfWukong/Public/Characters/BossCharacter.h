// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EEnemyState.h"
#include "Characters/EnemyCharacter.h"
#include "BossCharacter.generated.h"


class UBlackboardComponent;

UCLASS()
class LEGENDOFWUKONG_API ABossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	float AnimDuration;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	AAIController* Controller;

	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> AttackAnimations;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);
	
	UFUNCTION()
	void HandlePlayerDeath(bool bIsDead);

	float GetAnimDuration();
	
	void RandomAttack();
	
protected:
	virtual void BeginPlay() override;
};
