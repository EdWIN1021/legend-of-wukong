// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockOnComponent.generated.h"

/**
 * ULockOnComponent handles the logic for locking onto a target and adjusting the character's view and movement.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEGENDOFWUKONG_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULockOnComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	
	/** 
	 * Starts the lock-on process.
	 * @param Radius The radius within which to search for targets.
	 */
	UFUNCTION(BlueprintCallable)
	void StartLockOn(float Radius = 750.f);

private:
	/** The actor currently being targeted. */
	TWeakObjectPtr<AActor> TargetActor;

	/** The character that owns this component. */
	TObjectPtr<ACharacter> OwnerPawn;

	/** The player controller for the current player. */
	TWeakObjectPtr<APlayerController> Controller;

	/** The movement component of the owning character. */
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	/** The spring arm component for camera adjustments. */
	TObjectPtr<USpringArmComponent> SpringArm;
};
