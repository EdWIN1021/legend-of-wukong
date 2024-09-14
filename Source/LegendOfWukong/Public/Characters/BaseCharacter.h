// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAttribute.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"



UCLASS()
class LEGENDOFWUKONG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//delete
	UPROPERTY(EditAnywhere)
	TMap<EAttribute, float> Attributes;

	UFUNCTION(BlueprintCallable)
	virtual void ReduceHealth(float Amount) {};

	virtual float ApplyDamage() { return 0; };
};
