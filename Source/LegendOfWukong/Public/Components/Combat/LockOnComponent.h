// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyCharacter.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockOnComponent,
	OnUpdatedTargetDelegate,
	AActor*,
	NewTargetActorRef
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEGENDOFWUKONG_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULockOnComponent();

	TWeakObjectPtr<AEnemyCharacter> TargetEnemy;
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

	UFUNCTION(BlueprintCallable)
	void ToggleLockOn();
	
	void StartLockOn();
	void EndLockOn();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	float LockOnRadius = 750.f;

	/** The character that owns this component. */
	TWeakObjectPtr<ACharacter> Owner;
	
	/** The spring arm component for camera adjustments. */
	TWeakObjectPtr<USpringArmComponent> SpringArm;

	/** The player controller for the current player. */
	TWeakObjectPtr<APlayerController> Controller;

	/** The movement component of the owning character. */
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	double AutoEndLockOnDistance = 1000.f;
};
