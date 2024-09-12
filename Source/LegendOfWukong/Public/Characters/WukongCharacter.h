// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Fighter.h"
#include "WukongCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter, public IFighter
{
	GENERATED_BODY()

public:
	virtual float GetDamage() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;
};
