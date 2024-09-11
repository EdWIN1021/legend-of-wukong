// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WukongAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "WukongCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()



protected:
	virtual void BeginPlay() override;

private:
	// mapping context
	// Movement
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;
};
