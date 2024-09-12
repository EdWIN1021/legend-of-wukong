// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/BTT_ChargeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;
	MoveCompletedDelegate.BindUFunction(
		this,
		"HandleMoveCompleted"
	);
}



EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	if (!ControllerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get AI Controller"));
		return EBTNodeResult::Failed;
	}

	CharacterRef = ControllerRef->GetCharacter();
	if (!CharacterRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast to ABossCharacter"));
		return EBTNodeResult::Failed;
	}
	
	BossAnim = Cast<UBossAnimInstance>(CharacterRef->GetMesh()->GetAnimInstance());
	
	if (!BossAnim)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast to UBossAnimInstance"));
		return EBTNodeResult::Failed;
	}

	BossAnim->bIsCharging = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyToCharge"),false);
	
	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector PlayerLocation = Player->GetActorLocation();

	FAIMoveRequest MoveRequest(PlayerLocation);  
	MoveRequest.SetUsePathfinding(true);        
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);  

	ControllerRef->MoveTo(MoveRequest);          
	ControllerRef->SetFocus(Player);

	ControllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);
}

void UBTT_ChargeAttack::HandleMoveCompleted()
{
	BossAnim->bIsCharging = false;
	FTimerHandle AttackTimerHandle;
	CharacterRef->GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&UBTT_ChargeAttack::FinishAttackTask,
		1.0f,
		false
	);
	
}

void UBTT_ChargeAttack::FinishAttackTask()
{
	UE_LOG(LogTemp, Warning, TEXT("Task in Finshed!"))
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsReadyToCharge"));
	if(bIsReadyToCharge){
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyToCharge"), false);
		ChargeAtPlayer();
	}
}
