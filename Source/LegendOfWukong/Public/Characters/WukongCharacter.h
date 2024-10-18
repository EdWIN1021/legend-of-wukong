// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "PlayerState/WukongPlayerState.h"
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
	float JumpCost = 5.0f;
	
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
	
	void AutoEndLock(AActor* Actor);

	virtual void ReduceHealth(float Amount) override;
	
	UFUNCTION()
	void EnableStore();

	UPROPERTY()
	bool CanTakeDamage = false;
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	FORCEINLINE AWukongPlayerState* GetWukongPlayerState() const { return  CastChecked<AWukongPlayerState>(GetPlayerState()); };

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;

	AWukongHUD* GetWukongHUD();
};
