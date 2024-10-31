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
	double StaminaRestoreRate = 10.0f;
	
	void AutoEndLock(AActor* Actor);

	virtual void ReduceHealth(float Amount) override;

	bool bCanRestore = false;

	virtual void PossessedBy(AController* NewController) override;
	
protected:
	virtual void BeginPlay() override;

private:
	void FinishPadAnim();
	bool bCanTakeDamage = true;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;

	/**
	 * Retrieves the Wukong HUD instance.
	 *
	 * @return A pointer to the AWukongHUD instance associated with this actor.
	 */
	AWukongHUD* GetWukongHUD();
};
