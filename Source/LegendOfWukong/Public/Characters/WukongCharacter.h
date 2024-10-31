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

	virtual void PossessedBy(AController* NewController) override;

	void AutoEndLock(AActor* Actor);

	virtual void ReduceHealth(float Amount) override;
	
protected:
	virtual void BeginPlay() override;

private:
	bool bCanTakeDamage = true;

	// lock on anim
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;

	/**
	 * Retrieves the Wukong HUD instance.
	 *
	 * @return A pointer to the AWukongHUD instance associated with this actor.
	 */
	AWukongHUD* GetWukongHUD();
};
