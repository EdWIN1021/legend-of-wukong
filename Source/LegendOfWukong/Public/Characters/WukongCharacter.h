// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "WukongCharacter.generated.h"


class AWukongHUD;
class AWukongPlayerState;
class UCombatComponent;
class ULockOnComponent;



UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AWukongCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULockOnComponent> LockonComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCombatComponent> CombatComp;
	
	UPROPERTY(EditAnywhere)
	float SprintCost = 1.0f;
	
	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	double StaminaRestoreRate = 10.0;

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration = 2.0f;
	
	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();

	UFUNCTION(BlueprintCallable)
	void Pad();

	const float PadCost = 2.0f;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* PadAnimMontage;
	
	UFUNCTION(BlueprintCallable)
	void RestoreStamina();

	void ReduceStamina(float Amount);

	bool HasEnoughStamina(float Cost);
	
	void AutoEndLock(AActor* Actor);

	virtual void ReduceHealth(float Amount) override;
	
	UFUNCTION(BlueprintCallable)
	void EnableStore();

	bool bCanRestore = false;

	/*   */
	virtual void PossessedBy(AController* NewController) override;

	
protected:
	virtual void BeginPlay() override;

private:
	void FinishPadAnim();
	bool bCanTakeDamage = true;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;

	/*  */
	AWukongHUD* GetWukongHUD();
};
