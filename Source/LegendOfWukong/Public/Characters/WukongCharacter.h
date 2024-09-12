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
class LEGENDOFWUKONG_API AWukongCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AWukongCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULockOnComponent* LockonComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTraceComponent* TraceComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlockComponent* BlockComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UActionsComponent* ActionsComp;

	
	virtual float ApplyDamage() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWukongAnimInstance* WukongAnim;
};
