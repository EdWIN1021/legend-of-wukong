// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDOFWUKONG_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	
	UPROPERTY(VisibleAnywhere)
	bool bCanAttack = true;
	
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat");
	bool bIsAttacking = false;
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
