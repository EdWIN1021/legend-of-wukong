// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/MovementComponent.h"
#include "WukongCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AWukongCharacter();

	// delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULockOnComponent* LockonComp;

	// delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	// delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTraceComponent* TraceComp;

	// delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlockComponent* BlockComp;

	UPROPERTY(EditAnywhere)
	float SprintCost = 0.1f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	double StaminaRestoreRate = 10.0;

	UPROPERTY(EditAnywhere)
	bool bCanRestore = true;

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration = 2.0f;
	
	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();

	UFUNCTION(BlueprintCallable)
	void RestoreStamina();

	void ReduceStamina(float Amount);

	bool HasEnoughStamina(float Cost);

	UFUNCTION()
	void EnableStore();
	
	virtual float ApplyDamage() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;
};
