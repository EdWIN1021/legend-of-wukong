// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttact.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API UBTT_MeleeAttact : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_MeleeAttact();
		
	FScriptDelegate MoveDelegate;

	bool bIsFinish = false;

	UPROPERTY(EditAnywhere)
	float AttackRadius = 500.0f;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 100.0f;
	
	UFUNCTION()
	void FinishAttackTask();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
