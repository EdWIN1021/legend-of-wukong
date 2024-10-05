// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDOFWUKONG_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimations;

	ABaseCharacter* CharacterRef;

	UPROPERTY(VisibleAnywhere )
	int ComboCounter = 0;
	
	UPROPERTY(VisibleAnywhere )
	bool bCanAttack = true;

	UPROPERTY(EditAnywhere)
	float StaminaCost = 5.0f;
	
	UFUNCTION(BlueprintCallable)
	void ComboAttack();

	UFUNCTION(BlueprintCallable)
	void HandleRestAttack();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
