// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Enemy.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(EditAnywhere)
	float Speed = 400.f;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowLockOnUI();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HideLockOnUI();

	virtual void Tick(float DeltaTime) override;
};
