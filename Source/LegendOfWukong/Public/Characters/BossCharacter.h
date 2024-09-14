// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EEnemyState.h"
#include "AnimInstances/BossAnimInstance.h"
#include "Characters/EnemyCharacter.h"
#include "BossCharacter.generated.h"


class UBlackboardComponent;

UCLASS()
class LEGENDOFWUKONG_API ABossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	float AnimDuration;

	void RandomAttack();
    
	float GetAnimDuration();
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> AttackAnimations;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);
	
	virtual float ApplyDamage() override;
	virtual void ReduceHealth(float Amount) override;
	
protected:
	virtual void BeginPlay() override;
 };
