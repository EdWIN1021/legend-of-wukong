// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTT_MeleeAttact.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/BossCharacter.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_MeleeAttact::UBTT_MeleeAttact()
{
	MoveDelegate.BindUFunction(this, "FinishAttackTask");
	bNotifyTick = true;
}

void UBTT_MeleeAttact::FinishAttackTask()
{
	bIsFinish = true;
}

EBTNodeResult::Type UBTT_MeleeAttact::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinish = false;
	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));

	if(Distance > AttackRadius)
	{
		APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		FAIMoveRequest MoveRequest(Player);  
		MoveRequest.SetUsePathfinding(true);        
		MoveRequest.SetAcceptanceRadius(AcceptanceRadius);  

		OwnerComp.GetAIOwner()->MoveTo(MoveRequest);          
		OwnerComp.GetAIOwner()->SetFocus(Player);
		OwnerComp.GetAIOwner()->ReceiveMoveCompleted.AddUnique(MoveDelegate);
	}
	else
	{
		Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetCharacter())->RandomAttack();

		FTimerHandle AttackTimerHandle;
		OwnerComp.GetAIOwner()->GetCharacter()->GetWorldTimerManager().SetTimer(
			AttackTimerHandle,
			this,
			&UBTT_MeleeAttact::FinishAttackTask,
			Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetCharacter())->GetAnimDuration(),
			false
			);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttact::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(!bIsFinish)
	{
		return;
	} 
	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(MoveDelegate);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
