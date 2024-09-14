// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Components/StatsComponent.h"
#include "WukongCharacter.generated.h"

UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AWukongCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULockOnComponent* LockonComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTraceComponent* TraceComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlockComponent* BlockComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere)
	float SprintCost = 1.0f;

	UPROPERTY(EditAnywhere)
	float PadCost = 5.0f;
	
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

	UPROPERTY(EditAnywhere)
	bool bIsPad = false;
	
	UFUNCTION(BlueprintCallable)
	void Pad();
	
	virtual void ReduceHealth(float Amount) override;
	
	UFUNCTION(BlueprintCallable)
	void RestoreStamina();

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);

	bool HasEnoughStamina(float Cost);
		
	UPROPERTY(EditAnywhere)
	UAnimMontage* PadAnimMontage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* DeadthAnimMontage;

	void AutoEndLock(AActor* Actor);
	
	UFUNCTION()
	void EnableStore();
	
	virtual float ApplyDamage() override;

	UFUNCTION(BlueprintPure)
	virtual float GetPercentage(EAttribute Current, EAttribute Max);

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	UFUNCTION()
	void FinishPadAnim();
	bool CanTakeDamage();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;
};
