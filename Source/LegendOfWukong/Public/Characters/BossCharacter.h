// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EEnemyState.h"
#include "Characters/EnemyCharacter.h"
#include "BossCharacter.generated.h"


class UBlackboardComponent;

UCLASS()
class LEGENDOFWUKONG_API ABossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	UBlackboardComponent* BlackboardComp;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);

protected:
	virtual void BeginPlay() override;
 };
