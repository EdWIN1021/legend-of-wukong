// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BossAnimInstance.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BTTaskNode.h"



#include "BTT_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API UBTT_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	
	UBTT_ChargeAttack();
	

	AAIController* ControllerRef;

	ACharacter* CharacterRef;

	UBossAnimInstance* BossAnim;

	FScriptDelegate MoveCompletedDelegate;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 100.0f;

	UFUNCTION()
	void HandleMoveCompleted();

	UFUNCTION()
	void FinishAttackTask();
	
	void ChargeAtPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
