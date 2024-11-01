// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "WukongCharacter.generated.h"

class AWukongHUD;
class AWukongPlayerState;
class ULockOnComponent;

UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AWukongCharacter();

	/**
	 * Retrieves the Lock-On component.
	 *
	 * @return A pointer to the ULockOnComponent instance.
	 */
	ULockOnComponent* GetLockOnComponent() { return LockOnComp; };
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	virtual void BeginPlay() override;

private:
	bool bCanTakeDamage = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<ULockOnComponent> LockOnComp;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnimInstance;
	
	/**
	 * Retrieves the Wukong HUD instance.
	 *
	 * @return A pointer to the AWukongHUD instance associated with this actor.
	 */
	AWukongHUD* GetWukongHUD();
};
