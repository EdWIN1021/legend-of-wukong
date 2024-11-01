// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "EAttribute.h"
#include "GameplayEffect.h"
#include "DataAssets/DataAsset_Abilities.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class UTraceComponent;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetDeadSignature);

UCLASS()
class LEGENDOFWUKONG_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;

	UPROPERTY(BlueprintAssignable)
	FOnTargetDeadSignature OnTargetDead;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnim;
	
	UFUNCTION(BlueprintPure)
	virtual float GetPercentage(EAttribute Current, EAttribute Max);
	
	UFUNCTION(BlueprintCallable)
	virtual void ReduceHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath(){};

	virtual float ApplyDamage();

	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	UAttributeSet* GetAttributeSet() const { return AttributeSet; };
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component | Trace")
	TObjectPtr<UTraceComponent> TraceComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbilitySystem | GameplayEffects")
	TSubclassOf<UGameplayEffect> InitialAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameplayAbilitySystem | GameplayAbilities")
	UDataAsset_Abilities* AbilityDataAsset;

	/* Initializes character attributes using a gameplay effect */
	void InitializeAttributes() const;

	/* Grants the character their default abilities */
	void InitializeAbilities() const;
};
