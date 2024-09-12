// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/ToggleTraceNotifyState.h"

#include "Components/Combat/TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UTraceComponent* TraceComp = MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();

	if(!IsValid(TraceComp))
	{
		return;
	}
	TraceComp->bIsAttacking = true;
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UTraceComponent* TraceComp = MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();

	if(!IsValid(TraceComp))
	{
		return;
	}
	TraceComp->bIsAttacking = false;
}
