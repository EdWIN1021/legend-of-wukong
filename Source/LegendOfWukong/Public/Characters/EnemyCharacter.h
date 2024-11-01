// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "UI/WukongHUD.h"
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

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	/** Delegates*/
	UPROPERTY(BlueprintAssignable, Category="Enemy Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Enemy Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(EditAnywhere)
	float Speed = 400.f;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowLockOnUI();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HideLockOnUI();

	virtual void HandleDeath() override;

	void FinishDeathAnim();
	
	virtual void Tick(float DeltaTime) override;

protected:
	void BindDelegates();
	
private:
	void EndLockOn();
};
