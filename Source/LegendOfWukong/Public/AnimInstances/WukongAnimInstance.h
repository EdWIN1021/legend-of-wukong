// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WukongAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API UWukongAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float IdleTimeout = 0;
	
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);

	UFUNCTION(BlueprintCallable)
	void UpdateDirection();

	UFUNCTION(BlueprintCallable)
	void UpdateShouldPlayRelaxAnim(float DeltaSeconds, float WaitTime);

	UFUNCTION(BlueprintCallable)
	void UpdateVelocity();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bShouldPlayRelaxAnim = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentDirection = 0.0f;
};
