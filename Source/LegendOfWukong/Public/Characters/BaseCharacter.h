// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class UStartupAbilitiesAsset;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class LEGENDOFWUKONG_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTraceComponent* TraceComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnim;
	
	UFUNCTION(BlueprintPure)
	virtual float GetPercentage(EAttribute Current, EAttribute Max);
	
	UFUNCTION(BlueprintCallable)
	virtual void ReduceHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath(){};

	virtual float ApplyDamage();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameplayEffect | Attributes")
	TSubclassOf<UGameplayEffect> InitialAttributes;

	void InitializeAttributes() const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameplayAbilities | StartupAbilities")
	UStartupAbilitiesAsset* StartupAbilitiesDataAsset;

	void InitializeAbilities(int32 ApplyLevel = 1) const;
};
